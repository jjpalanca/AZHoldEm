cmake_minimum_required(VERSION 3.13)
project(AZHoldEm)

set(CMAKE_CXX_STANDARD 14)

add_executable(AZHoldEm
        52Cards.hpp
        Card.cpp
        catch.hpp
        PokerHand.hpp
        Dealer.hpp
        Player.hpp
        main.cpp)