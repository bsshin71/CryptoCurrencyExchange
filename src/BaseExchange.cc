#include <BaseExchange.hpp>
#include <BCMath.hpp>
#include <Goldilocks.hpp>
#include <errno.h>
#include <cstring>

namespace exchange { 

BaseExchange :: BaseExchange (const int aScale, 
                              const int aDatabaseType ) : 
    mDB(NULL), 
    mScale ( aScale ), 
    mDatabaseType(aDatabaseType)
  {}

BaseExchange :: ~BaseExchange () 
{
  if ( mDB != NULL  ) 
  {
    delete mDB; 
  }
}

int BaseExchange :: FillRequest ( const Request& aRequest, uint64 &aReqNo ) 
{

  int sRC = 0; 
  BCMath::bcscale ( 18 ) ;
  size_t sVectorSize = 0 ;
  ResultVector sVector; 
  DBRequest sDBRequest; 
  int sCompareResult = 0; 

  // initialize  
  memset (&sDBRequest, 0x00, sizeof(DBRequest));

  // Copy aRequest to sDBRequest
  strncpy (sDBRequest.mCoin, aRequest.mCoin, MAX_COIN_NAME_LENGTH ) ;
  sDBRequest.mOrderType = aRequest.mOrderType;
  sDBRequest.mPosition = aRequest.mPosition;
  sDBRequest.mPrice = aRequest.mPrice;
  strncpy (sDBRequest.mQty, aRequest.mQty, MAX_FLOATING_LENGTH ) ;
  strncpy (sDBRequest.mAvailQty, aRequest.mQty, MAX_FLOATING_LENGTH ) ;
  sDBRequest.mOrderNo = aRequest.mOrderNo;
  sDBRequest.mProcess = PROCESSING; 

  sRC = mDB->BeginTransaction () ;

  // Insert my request 
  sRC = mDB->InsertNewRequest ( &sDBRequest ) ;
  if ( sRC ) {
    return sRC ;
  }
  // set request no 
  aReqNo = sDBRequest.mTicketNo;


  // Get result to match 
  sRC = mDB->FindMatchRecords ( &sDBRequest, sVector ) ;
  if ( sRC ) {
    return sRC ;
  }

  sVectorSize = sVector.size();

  // If empty result, there is no data to match with current request. 
  if ( sVectorSize == 0 && sDBRequest.mOrderType == LIMIT_ORDER) 
  {
    return mDB->Commit () ;
  } else if (sVectorSize == 0 && sDBRequest.mOrderType == MARKET_ORDER ) 
  {
    mDB->Rollback() ;
    throw ExchangeException ( "empty order book. could not place a market order.") ;
  }
  
  // Found to match
  
  for (auto it = sVector.begin(); it != sVector.end() ; ++it) 
  {

    BCMath sLeft  ( std::string( sDBRequest.mAvailQty) ) ; 
    BCMath sRight ( std::string( it->mAvailQty ) ) ; 

    
    if ( sLeft > sRight ) {
      sCompareResult = 1; 
    } else if ( sLeft < sRight ) {
      sCompareResult = -1 ;
    } else  { 
      sCompareResult = 0 ;
    }

    if ( sCompareResult == 1  ) 
    {
                           

      BCMath sResult = sLeft - sRight ;
      sRC = mDB->AjustAvailQty (sDBRequest.mTicketNo, 
                                sDBRequest.mCoin, 
                                (char*)sResult.toString().c_str(), 
                                PROCESSING ) ;

      strncpy (sDBRequest.mAvailQty , 
               sResult.toString().c_str(), 
               MAX_FLOATING_LENGTH );


      sRC = mDB->CloseRequest  ((*it).mTicketNo , sDBRequest.mCoin) ;

      sRC = mDB->BuildFill (sDBRequest.mCoin, 
                            it->mPrice, 
                            (*it).mAvailQty, 
                            sDBRequest.mTicketNo, 
                            it->mTicketNo );
    } 
    else if ( sCompareResult == -1 ) 
    {


      BCMath sResult = sRight - sLeft ;
      sRC = mDB->CloseRequest  (sDBRequest.mTicketNo, sDBRequest.mCoin ) ;

      sRC = mDB->AjustAvailQty (it->mTicketNo, 
                                sDBRequest.mCoin, 
                                (char*)sResult.toString().c_str(), 
                                PROCESSING
                               ) ;

      sRC = mDB->BuildFill (sDBRequest.mCoin, 
                            it->mPrice, 
                            sDBRequest.mAvailQty, 
                            sDBRequest.mTicketNo, 
                            it->mTicketNo );

      // No need to process next 
      break; 
    }
    else 
    {
      sRC = mDB->CloseRequest ( sDBRequest.mTicketNo , sDBRequest.mCoin) ;
      sRC = mDB->CloseRequest ( it->mTicketNo , it->mCoin) ;

      sRC = mDB->BuildFill (sDBRequest.mCoin, 
                            it->mPrice, 
                            it->mAvailQty, 
                            sDBRequest.mTicketNo,
                            it->mTicketNo );
      // No need to process next 
      break; 
    }
  }

  if ( sCompareResult == 1 && sDBRequest.mOrderType == MARKET_ORDER ) 
  {
    sRC = mDB->CloseRequest ( sDBRequest.mTicketNo , sDBRequest.mCoin) ;
  }

  // if market order,  cancel the request placed order with the left quantity. 
    
  return mDB->Commit () ;

} 

int BaseExchange :: OpenDatabase (const std::string& aUser, 
                                  const std::string& aPassword, 
                                  const std::string& aDSN ) 
{
  switch ( mDatabaseType ) 
  {
    case GOLDILOCKS : 
      mDB = new Goldilocks ( aUser, aPassword, aDSN, mLogOption, mScale) ;
      if ( mDB == NULL ) { 
        return errno; 
      } 
      break; 

    default : 
      return NOT_SUPPORTED_DATABASE; 
      break;  
  } ; 
  return mDB->OpenDatabase () ;
}


int BaseExchange :: CloseDatabase () 
{
  return mDB->CloseDatabase () ;
}


int BaseExchange :: GetOfferStatus (OfferVector &aOfferVector) 
{

  return mDB->GetOfferStatus (aOfferVector);
} 

}

