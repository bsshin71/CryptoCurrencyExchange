#pragma once 
#include <DB.hpp>
#include <map>

namespace exchange { 


typedef std::map<std::string, char*> QueryMap ;

#define MAX_QUERY_STRING_LENGTH 1024 

class Goldilocks : public IDatabase  {

 public : 
  Goldilocks (const std::string& aUser, 
              const std::string& aPassword, 
              const std::string& aDSN, 
              const int aLogOption, 
              const int aPrecision ) ;

  virtual ~Goldilocks () ; 
  int OpenDatabase ( );
  int BeginTransaction (); 
  int Commit();
  int Rollback();
  int CloseDatabase();


  int InsertNewRequest ( DBRequest* aRequest ) ;
  int FindMatchRecords ( DBRequest* aResult, ResultVector &aVector ) ;
  int AjustAvailQty ( uint64 aNo, char *aCoin,  char* aQty , int aProcess )  ;
  int CloseRequest (uint64 aNo, char *aCoin ) ;
  int BuildFill (char * aCoin, 
                 uint64 aPrice,
                 char*  aQty, 
                 uint64 aAskNo, 
                 uint64 aBidNo ) ;

  int GetOfferStatus ( OfferVector &aOfferVector ) ;


 private :
  std::string mUser;
  std::string mPassword;
  std::string mDSN;
  int         mLogOption;
  int         mScale;
  QueryMap mQueryMap; 

  int         mIsOpened ;

  int buildQueryMap ( );

};  

} 
