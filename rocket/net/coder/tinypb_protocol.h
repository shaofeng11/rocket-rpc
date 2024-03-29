#ifndef ROCKET_NET_TINYPB_PROTOCOL_H__
#define ROCKET_NET_TINYPB_PROTOCOL_H__

#include"abstract_protocol.h"

namespace rocket{

struct TinyPBProtocol:public AbstractProtocol{

public:
    static char PB_START;
    static char PB_END;
public:
    int32_t m_pk_len{0};
    int32_t m_req_id_len{0};
    int32_t m_method_name_len{0};
    std::string m_method_name;
    int32_t m_err_code{0};
    int32_t m_err_info_len{0};
    std::string m_err_info;
    std::string m_pb_data;
    int32_t m_check_sum{0};

    bool m_parser_success{false};
};

}

#endif