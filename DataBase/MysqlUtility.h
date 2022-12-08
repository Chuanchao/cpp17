//
// Created by Chuanchao Lyu on 2022/11/29.
//

#ifndef CPP17_MYSQLUTILITY_H
#define CPP17_MYSQLUTILITY_H

#include "LogWrapper.h"
#include <functional>
#include <mysql++/mysql++.h>

namespace HFTrading{
    class MysqlUtility:public LoggerBase{
    public:
        bool queryByExec(const std::string& querystr, mysqlpp::Connection& sql);

        template<typename RetValue>
        bool queryByStore(const std::string& querystr, RetValue& value, mysqlpp::Connection& sql,
                          std::function<void(const mysqlpp::StoreQueryResult&,RetValue&)> convertor){
            try{
                auto query = sql.query(querystr);
                auto res = query.store();
                if(res.num_rows()>0 and convertor){
                    convertor(res,value);
                    return true;
                }
                else{
                    _logger->warn("Exectution {} FAILED!",querystr);
                    return false;
                }
            }
            catch(mysqlpp::BadQuery& ex){
                _logger->warn("Exception::{} FIALED!,{}",querystr,ex.what());
                return false;
            }

        }

    };
}


#endif //CPP17_MYSQLUTILITY_H
