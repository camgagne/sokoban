// Copyright 2025 Cameron Gagne

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Sokoban.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testCantMove) {
    SB::Sokoban s;
    std::ifstream inputFile;
    inputFile.open("level1.lvl");
    inputFile >> s;

    s.movePlayer(SB::Direction::Down);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 7);

    s.movePlayer(SB::Direction::Up);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 6);

    s.movePlayer(SB::Direction::Right);
    BOOST_REQUIRE_EQUAL(s.playerLoc().x, 4);

    s.movePlayer(SB::Direction::Left);
    BOOST_REQUIRE_EQUAL(s.playerLoc().x, 3);
}

BOOST_AUTO_TEST_CASE(testIgnoreBoxes) {
    SB::Sokoban s;
    std::ifstream inputFile;
    inputFile.open("pushdown.lvl");
    inputFile >> s;

    s.movePlayer(SB::Direction::Down);
    s.movePlayer(SB::Direction::Down);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 3);
}

BOOST_AUTO_TEST_CASE(testBoxBox) {
    SB::Sokoban s;
    std::ifstream inputFile;
    inputFile.open("level2.lvl");
    inputFile >> s;

    s.movePlayer(SB::Direction::Up);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 5);
}

BOOST_AUTO_TEST_CASE(testMoveOffScreen) {
    SB::Sokoban s;
    std::ifstream inputFile;
    inputFile.open("pushup.lvl");
    inputFile >> s;

    s.movePlayer(SB::Direction::Down);
    s.movePlayer(SB::Direction::Down);
    s.movePlayer(SB::Direction::Down);
    s.movePlayer(SB::Direction::Down);
    s.movePlayer(SB::Direction::Down);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 4);
}

BOOST_AUTO_TEST_CASE(testLotsOfBoxes) {
    SB::Sokoban s;
    std::ifstream inputFile;
    inputFile.open("level5.lvl");
    inputFile >> s;

    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Left);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Right);
    BOOST_REQUIRE_EQUAL(s.isWon(), true);
}

BOOST_AUTO_TEST_CASE(testLotsOfTargets) {
    SB::Sokoban s;
    std::ifstream inputFile;
    inputFile.open("level6.lvl");
    inputFile >> s;

    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Down);
    s.movePlayer(SB::Direction::Left);
    s.movePlayer(SB::Direction::Left);
    s.movePlayer(SB::Direction::Left);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Left);
    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Right);
    s.movePlayer(SB::Direction::Right);
    BOOST_REQUIRE_EQUAL(s.isWon(), true);
}

BOOST_AUTO_TEST_CASE(testMissingSymbol) {
    SB::Sokoban s;
    std::ifstream inputFile;
    inputFile.open("swapoff.lvl");
    inputFile >> s;


    s.movePlayer(SB::Direction::Up);
    s.movePlayer(SB::Direction::Up);
    BOOST_REQUIRE_EQUAL(s.playerLoc().y, 1);
}

