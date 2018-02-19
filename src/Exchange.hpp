#pragma once 

/******************************************************************************

  Writer : ckh0618@sunjesoft.com 
  Description : Definition of interface of exchange model 

******************************************************************************/

#include <common.hpp>
#include <string>
#include <DB.hpp>
#include <vector>

namespace exchange {

typedef std::vector<Offer>     OfferVector ; 

class IExchange 
{
 public :  
  virtual ~IExchange () ;
  virtual int FillRequest ( const Request& aRequest, 
                            uint64&  aReqNo ) = 0;

  virtual int OpenDatabase (const std::string& aUser, 
                            const std::string& aPassword, 
                            const std::string& aDSN ) = 0 ;
  virtual int GetOfferStatus (OfferVector &aOfferVector ) = 0;

  virtual int CloseDatabase () = 0; 

}; 

}


