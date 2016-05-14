////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file	network\NetworkUtil.h
///
/// @brief 定义一些网络API
////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief  根据主机IP获取网关地址，保存到参数pGateway中，pGateway的长度至少为16.
 * @param pHostIP		主机IP地址
 * @param pGateway	网关地址输出字符串
 * @return  返回是否成功获取网关地址
 */
bool getGatewayByHostIP(const char* pHostIP, char * pGateway);