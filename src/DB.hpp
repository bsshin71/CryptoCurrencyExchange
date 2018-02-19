#pragma once 
#include <ExchangeException.hpp>
#include <common.hpp>
#include <string>
#include <vector> 

namespace exchange {
typedef std::vector<DBRequest> ResultVector ;
typedef std::vector<Offer>     OfferVector ; 

class IDatabase 
{
 public : 
  virtual ~IDatabase ();
  virtual int OpenDatabase ()=0;
  virtual int BeginTransaction ()=0; 
  virtual int Commit()=0;
  virtual int Rollback()=0;
  virtual int CloseDatabase() = 0;

  
  virtual int InsertNewRequest ( DBRequest* aRequest ) = 0;
  virtual int FindMatchRecords ( DBRequest* aRequest,
                                 ResultVector &aVector ) =0 ;

  virtual int AjustAvailQty (uint64 aNo, 
                             char*  aCoin, 
                             char*  aQty, 
                             int    aProcess  ) =0 ;

  virtual int CloseRequest  (uint64 aNo, char *aCoin ) = 0 ; 
                             
  virtual int BuildFill (char *aCoin, 
                         uint64 aPrice, 
                         char*  aQty, 
                         uint64 aAskNo, 
                         uint64 aBindNo ) =0;

  virtual int GetOfferStatus ( OfferVector &aOfferVector ) = 0 ;



};



}


