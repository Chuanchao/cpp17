//
// Created by Chuanchao Lyu on 2022/11/29.
//

#include "MysqlUtility.h"

using namespace HFTrading;

bool MysqlUtility::queryByExec(const std::string& querystr, mysqlpp::Connection& sql) {
    try
    {
        auto query = sql.query(querystr);
        if(query.exec())
        {
            return true;
        }else{
            _logger->warn("Exectution {} FAILED!",querystr);
            return false;
        }
    }
    catch (mysqlpp::BadQuery& e)
    {
        _logger->warn("Exception:: {} FAILED!",querystr);
        return false;
    }
}