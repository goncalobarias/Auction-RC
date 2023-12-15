#ifndef __PERSISTANCE_HPP__
#define __PERSISTANCE_HPP__

#include "../lib/utils.hpp"

#include <cstring>
#include <dirent.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

int checkRegister(const std::string UID);
int checkLoggedIn(std::string UID);
int checkLoginMatch(std::string UID, std::string password);
int registerUser(std::string UID, std::string password);
int loginUser(std::string UID);
int logoutUser(std::string UID);
int unregisterUser(std::string UID);
void getAuctionTime(std::string AID, time_t &currentTime, uint32_t &fullTime,
                    uint32_t &duration);
uint8_t checkAuctionExpiration(std::string AID);
int getAuctions(std::string path, std::vector<Auction> &auctions);
int closeAuction(std::string AID);
int checkAuctionExists(std::string AID);
int checkUserHostedAuction(std::string UID, std::string AID);
int openAuction(std::string newAID, std::string UID, std::string auctionName,
                std::string assetfName, uint32_t startValue, uint32_t duration);
std::string getNewAID();
int getAuctionRecord(std::string AID, std::string &info);
int bidAuction(std::string AID, std::string UID, uint32_t value);
int getAuctionAsset(std::string AID, std::string &fPath);

#endif // __PERSISTANCE_HPP__
