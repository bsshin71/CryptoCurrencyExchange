#pragma once 


#include <Exchange.hpp>
#include <vector> 

namespace exchange { 
// Base Exchange model. 

typedef std::vector<DBRequest> ResultVector ;

class BaseExchange : public IExchange 
{ 
 public : 
  BaseExchange ( const int aScale , 
                 const int aDatabaseType) ;

  virtual ~BaseExchange () ;

  virtual int OpenDatabase (const std::string& aUser, 
                            const std::string& aPassword, 
                            const std::string& aDSN ) ;


  virtual int FillRequest ( const Request& aRequest, uint64& aReqNo );

  virtual int GetOfferStatus ( OfferVector &aOfferVector ) ;

 private : 
  int CloseDatabase () ;
  IDatabase  *mDB ;
  int         mScale;
  int         mDatabaseType; 
  int         mLogOption ;

 private :
  

}; 

}

