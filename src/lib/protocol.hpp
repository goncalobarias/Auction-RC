#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

#include "utils.hpp"

#include <string>

class Packet {
  public:
    virtual std::string serialize() = 0;
    virtual int deserialize(std::string &buffer) = 0;

    virtual ~Packet() = default;
};

// Send login packet (LIN)
class LINPacket : public Packet {
  public:
    static constexpr const char *ID = "LIN";
    std::string UID;
    std::string password;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive login packet (RLI)
class RLIPacket : public Packet {
  public:
    static constexpr const char *ID = "RLI";
    std::string status;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Send logout packet (LOU)
class LOUPacket : public Packet {
  public:
    static constexpr const char *ID = "LOU";
    std::string UID;
    std::string password;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive logout packet (RLO)
class RLOPacket : public Packet {
  public:
    static constexpr const char *ID = "RLO";
    std::string status;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Send register packet (UNR)
class UNRPacket : public Packet {
  public:
    static constexpr const char *ID = "UNR";
    std::string UID;
    std::string password;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive register packet (RUR)
class RURPacket : public Packet {
  public:
    static constexpr const char *ID = "RUR";
    std::string status;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Send open packet (OPA)
class OPAPacket : public Packet {
  public:
    static constexpr const char *ID = "OPA";
    std::string UID;
    std::string auctionName;
    FileInfo fInfo;
    int startValue;
    int timeActive;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive open packet (ROA)
class ROAPacket : public Packet {
  public:
    static constexpr const char *ID = "AID";
    std::string status;
    int AID;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Send close packet (CLS)
class CLSPacket : public Packet {
  public:
    static constexpr const char *ID = "CLS";
    std::string UID;
    std::string password;
    int AID;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive close packet (RCL)
class RCLPacket : public Packet {
  public:
    static constexpr const char *ID = "RCL";
    std::string status;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Send myAuctions packet (LMA)
class LMAPacket : public Packet {
  public:
    static constexpr const char *ID = "LMA";
    std::string UID;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive myAuctions packet (RMA)
class RMAPacket : public Packet {
  public:
    static constexpr const char *ID = "RMA";
    std::string status;
    std::string auctionsInfo;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Send myBids packet (LMB)
class LMBPacket : public Packet {
  public:
    static constexpr const char *ID = "LMB";
    std::string UID;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive myBids packet (RMB)
class RMBPacket : public Packet {
  public:
    static constexpr const char *ID = "RMB";
    std::string status;
    std::string auctionsInfo;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Send list packet (LST)
class LSTPacket : public Packet {
  public:
    static constexpr const char *ID = "LST";

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive list packet (RLS)
class RLSPacket : public Packet {
  public:
    static constexpr const char *ID = "RLS";
    std::string status;
    std::string auctionsInfo;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Send bid packet (BID)
class BIDPacket : public Packet {
  public:
    static constexpr const char *ID = "BID";
    std::string UID;
    std::string password;
    int AID;
    int value;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive bid packet (RBD)
class RBDPacket : public Packet {
  public:
    static constexpr const char *ID = "RBD";
    std::string status;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Send showAsset packet (SAS)
class SASPacket : public Packet {
  public:
    static constexpr const char *ID = "SAS";
    int AID;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive showAsset packet (RSA)
class RSAPacket : public Packet {
  public:
    static constexpr const char *ID = "RSA";
    std::string status;
    FileInfo fInfo;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Send showRecord packet (SRC)
class SRCPacket : public Packet {
  public:
    static constexpr const char *ID = "SRC";
    int AID;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Receive showRecord packet (RRC)
class RRCPacket : public Packet {
  public:
    static constexpr const char *ID = "RRC";
    std::string status;
    std::string hostUID;
    std::string auctionName;
    std::string assetfName;
    int startValue;
    std::string startDateTime;
    int timeActive;
    std::string bidsInfo;
    std::string endDateTime;
    int endSecTime;

    std::string serialize();
    int deserialize(std::string &buffer);
};

// Error UDP packet (ERR)
class ERRPacket : public Packet {
  public:
    std::string serialize() { return "ERR\n"; }
    int deserialize(std::string &buffer) {
        (void)buffer; // unimplemented
        return 0;
    }
};

int sendUDPPacket(Packet &packet, struct addrinfo *res, int fd);

int receiveUDPPacket(std::string &response, struct addrinfo *res, int fd);

int sendTCPPacket(Packet &packet, int fd);

int receiveTCPPacket(std::string &response, int fd);

int verifyPacketFormat(std::string &buffer, std::string ID);

int readDelimiter(std::string &line);

int readFileInfo(std::string &line, FileInfo &fInfo);

void listAuctions(std::string auctions);

void listBids(std::string bidsInfo);

#endif // __PROTOCOL_HPP__
