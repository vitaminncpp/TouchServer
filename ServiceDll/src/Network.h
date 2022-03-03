#define LOG_ERR std::cerr << "Error At : " << __FILE__ << " : " << __LINE__ << std::endl
struct IPv4
{
    unsigned char s_b1, s_b2, s_b3, s_b4;
};

bool GetMyIP(struct IPv4& myIP);