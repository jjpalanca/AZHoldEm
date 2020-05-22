//
// Created by Rick Mercer on 2019-03-20.
//

// Beginning of a Unit test for PokerHand and its overloaded < operator
//#include "PokerHand.hpp"
//#include "52Cards.hpp"
//#include "catch.hpp"

TEST_CASE("testHighCard2") {
  PokerHand a(C5, C2, C3, C6, D7);
  PokerHand b(C2, C4, C8, D3, DA);
  REQUIRE(a < b);
  PokerHand c(C2, C3, C5, C8, DK);//Checks if comparing from greatest to least
  PokerHand d(C2, C3, C6, D7, DK);
  REQUIRE(not(c < d));
  PokerHand e(C2, C3, C6, C7, DK);//Checks if first element is equal to one another
  PokerHand f(C2, C3, C4, D8, DK);
  REQUIRE(e < f);
  PokerHand pair6(C3, S3, CQ, CK, CA);
  REQUIRE(pair6.getBestHand()==2);
}

//TEST PAIRS PokerHand pair(D2, H2, D3, S7, H6);
PokerHand pair2(C2, S2, CQ, CK, CA);
PokerHand pair3(C3, H3, H4, H5, S6);
PokerHand pair4(C4, S4, CQ, CK, CA);//checks to see if it compares properly
PokerHand pair5(C3, H3, H4, H5, S6);
PokerHand pair6(C3, S3, CQ, CK, CA);//Checks to see if it will properly grab the High card when pairs match
PokerHand pair7(C3, H3, H4, H5, S6);
PokerHand pair8(C3, S3, C5, C7, C8);//Checks to see if it will properly grab the High card when pairs match
PokerHand pair9(C3, H3, H4, H7, S8);
PokerHand pair10(C3, S3, C4, C7, C8);//Checks to see if it will properly grab the High card when pairs match
PokerHand pair11(C3, H3, H4, H7, S8);

TEST_CASE("testPairs2_3") {
  REQUIRE(pair2 < pair3);
  REQUIRE(not(pair4 < pair5));
  REQUIRE(pair6.getBestHand() == 2);//checks to see the best hand is a pair
  REQUIRE(pair7.getBestHand() == 2);//checks to see the best hand is a pair
  REQUIRE(not(pair6 < pair7));//Since both have the same pair, we compare the high cards.
  REQUIRE(pair8.getBestHand() == 2);
  REQUIRE(pair9.getBestHand() == 2);
  REQUIRE(not(pair8 < pair9));//Will go all the way to the last card, since others are the same
  REQUIRE(not(pair10 < pair11));//Should return false since it's a tie.
  REQUIRE(pair10 == pair11);//Should evaluate to true, since they are the same hand
}

PokerHand pair12(C3, S3, C4, C4, C8);//Checks to see if it will properly grab the Highest pair
PokerHand pair13(C3, H3, H5, H5, S7);
PokerHand pair14(C3, S3, C4, C4, C8);//Checks to see if it will properly grab the High card when pairs match
PokerHand pair15(C3, H3, H4, H4, S7);
PokerHand pair16(C3, S3, C4, C4, C8);//Checks to see if it will properly grab the High card when pairs match
PokerHand pair17(C3, H3, H4, H4, S7);

TEST_CASE("Test2Pairs") {
  REQUIRE(not(pair12.getBestHand() == 2));
  REQUIRE(pair13.getBestHand() == 3);
  REQUIRE(pair12 < pair13);//Checks to see if it will properly grab the Highest pair
  REQUIRE(pair14.getBestHand() == 3);//Checks to see if the best hand is a "TwoPair"
  REQUIRE(pair15.getBestHand() == 3);//Checks to see if the best hand is a "TwoPair"
  REQUIRE(not(pair14 < pair15));//If both pairs are a tie, go to the high card.
}

PokerHand Three1(CQ, CQ, SQ, D4, H5);
PokerHand Three2(DK, HK, SK, D5, H6);
PokerHand Three3(CA, CA, SA, D4, H5);
PokerHand Three4(DK, HK, SK, D5, H6);
PokerHand Three5(CK, CK, SK, D4, H5);
PokerHand Three6(DK, HK, SK, D5, H6);
PokerHand Three7(CK, CK, SK, D4, H6);
PokerHand Three8(DK, HK, SK, D5, H6);
PokerHand Three9(CK, D4, SK, CK, H6);
PokerHand Three10(DK, HK, SK, D5, H6);

TEST_CASE ("Test3ofAKind") {
  REQUIRE(Three1.ThreeOfAKind() == true);//Checks if "Three of a kind"
  REQUIRE(not(Three2.getBestHand() == 3));//Checks if "Three of a kind"
  REQUIRE(Three2.getBestHand() == 4);//Checks if "Three of a kind"
  REQUIRE(Three1 < Three2);//Checks if "Three1" 3 of a kind is less than "Three2"'s 3 of a kind.
  REQUIRE(not(Three3 < Three4));//Checks to make sure that one is less than the other.
  REQUIRE(Three5 < Three6);// If the 3 of a kind is the same, will it go to next high card
  REQUIRE(Three7 < Three8);// If the 3 of a kind and the first high card is the same, will it go to the next one.
  REQUIRE(Three9 < Three10);// Checks if order doesn't matter
}

PokerHand straight1(C2, C3, S4, D5, H6);
PokerHand straight2(D3, H4, S5, D6, H7);
PokerHand straight3(C5, C4, S2, D6, H3);
PokerHand straight4(D3, H4, S5, D6, H7);
PokerHand straight5(C5, C4, S6, D8, H7);
PokerHand straight6(D3, H4, S5, D6, H7);
PokerHand straight7(CA, C2, S3, D4, H5);
PokerHand straight8(D2, H3, S4, D5, H6);

TEST_CASE("Straight") {
  REQUIRE(straight1.Straight() == true);
  REQUIRE(straight2.Straight() == true);
  REQUIRE(straight1.getBestHand() == 5);
  REQUIRE(straight2.getBestHand() == 5);
  REQUIRE(straight1 < straight2);//Checks to see if it will get the high card, and if order doesn't matter.
  REQUIRE(straight3 < straight4);//Checks to see if order doesn't matter.
  REQUIRE(not(straight5 < straight6));//Checks to see if opposite would be true.
  REQUIRE(straight7 < straight8);//Checks to see if "Ace" has a value of 1.
}

PokerHand Flush1(C2, C3, C8, C5, C6);
PokerHand Flush2(D3, D4, D5, D6, D9);
PokerHand Flush3(C2, C3, C10, C5, C6);
PokerHand Flush4(D3, D4, D5, D6, D9);

TEST_CASE("Flush") {
  REQUIRE(Flush1.Flush() == true);
  REQUIRE(Flush2.Flush() == true);
  REQUIRE(Flush1.getBestHand() == 6);
  REQUIRE(Flush2.getBestHand() == 6);
  REQUIRE(Flush1 < Flush2);//Tests to see if it's grabbing the high card correctly.
  REQUIRE(not(Flush3 < Flush4));//Tests to see if it's grabbing the high card correctly.
}

PokerHand FullHouse1(C3, D3, H3, C5, D5);
PokerHand FullHouse2(C4, D4, H4, C3, D3);
PokerHand FullHouse3(C6, D6, H6, C2, D2);
PokerHand FullHouse4(C4, D4, H4, C3, D3);

TEST_CASE("FullHouse") {
  REQUIRE(FullHouse1.FullHouse() == true);
  REQUIRE(FullHouse2.FullHouse() == true);
  REQUIRE(FullHouse1.getBestHand() == 7);
  REQUIRE(FullHouse2.getBestHand() == 7);
  REQUIRE(FullHouse1 < FullHouse2);//Checks to see if it's comparing the three of a kind first
  REQUIRE(FullHouse3.FullHouse() == true);
  REQUIRE(FullHouse4.FullHouse() == true);
  REQUIRE(FullHouse3.getBestHand() == 7);
  REQUIRE(FullHouse4.getBestHand() == 7);
  REQUIRE(not(FullHouse3 < FullHouse4));//Checks to see if it's comparing the three of a kind first
}

PokerHand Fourofakind1(C3, D3, H3, S3, D5);
PokerHand Fourofakind2(C4, D4, H4, S4, D3);
PokerHand Fourofakind3(C5, D5, H5, S5, D2);
PokerHand Fourofakind4(C4, D4, H4, S4, D3);
PokerHand Fourofakind5(C5, D5, H5, S5, D2);
PokerHand Fourofakind6(C5, D5, H5, S5, D3);

TEST_CASE("FourOkAKind") {
  REQUIRE(Fourofakind1.FourOfAKind() == true);
  REQUIRE(Fourofakind2.FourOfAKind() == true);
  REQUIRE(Fourofakind1.getBestHand() == 8);
  REQUIRE(Fourofakind2.getBestHand() == 8);
  REQUIRE(Fourofakind1 < Fourofakind2);//Checks to see if the compare is working
  REQUIRE(not(Fourofakind3 < Fourofakind4));//Checks to see if the compare is working
  REQUIRE(Fourofakind5.FourOfAKind() == true);
  REQUIRE(Fourofakind6.FourOfAKind() == true);
  REQUIRE(Fourofakind5.getBestHand() == 8);
  REQUIRE(Fourofakind6.getBestHand() == 8);
  REQUIRE(Fourofakind5 < Fourofakind6);
}

PokerHand Strtflush1(C3, C4, C6, C5, C7);
PokerHand Strtflush2(D8, D4, D6, D5, D7);

TEST_CASE("StrtFlush") {
  REQUIRE(Strtflush1.getBestHand() == 9);
  REQUIRE(Strtflush2.getBestHand() == 9);
  REQUIRE(Strtflush1 < Strtflush2);
}

PokerHand Strtflush100(D8, D4, D6, D5, D7);
PokerHand Fourofakind100(C5, D5, H5, S5, D3);
PokerHand FullHouse100(C4, D4, H4, C3, D3);
PokerHand Flush100(D3, D4, D5, D6, D9);
PokerHand straight100(D2, H3, S4, D5, H6);
PokerHand Three100(CQ, CQ, SQ, D4, H5);
PokerHand Twopair100(C3, H3, H4, H4, S7);
PokerHand Onepair100(C3, H3, H4, H5, S6);
PokerHand HighCard100(C2, C4, C8, D3, DA);

TEST_CASE("Overall") {
  REQUIRE(Fourofakind100 < Strtflush100);
  REQUIRE(FullHouse100 < Fourofakind100);
  REQUIRE(Flush100 < FullHouse100);
  REQUIRE(straight100 < Flush100);
  REQUIRE(Three100 < straight100);
  REQUIRE(Twopair100 < Three100);
  REQUIRE(Onepair100 < Twopair100);
  REQUIRE(HighCard100 < Onepair100);
}
PokerHand g(CA, C2, S3, D4, H5);
PokerHand h(DK, HK, SK, D5, H6);
TEST_CASE("ace_low_straight"){
  REQUIRE(h.getBestHand()==4);
  REQUIRE(g.getBestHand()==5);
  REQUIRE(h<g);
}

/*
#include "PokerHand.hpp"
#include "52Cards.hpp"
#include "catch.hpp"

*/
/*TEST_CASE("testHighCard2") {
  //PokerHand a(C3, C4, D6, D7, DQ);
  //PokerHand b(C2, C5, C7, DJ, DK);
  PokerHand a(C10, CK, CQ, CA, CJ);
  PokerHand b(D10, DJ, DQ, DK, CA);
  REQUIRE(a.getBestHand() == 10);
  //REQUIRE(b.getBestHand() == 10);
  //REQUIRE(a < b);
}*//*


*/
/*//*
/ TEST PAIRS PokerHand pair(D2, H2, D3, S7, H6);
PokerHand pair2(C2, S2, CQ, CK, CA);
PokerHand pair3(C3, H3, H4, H5, S6);

TEST_CASE(" testPairs2_3") {
  REQUIRE(pair2 < pair3);
}*//*


TEST_CASE ("AceLowStraight") {
  PokerHand a(CA, C2, S3, D4, H5); // Ace low straight
  PokerHand b(DK, HK, SK, D5, H6); // 3 of a kind
  //REQUIRE(a.getBestHand() ==  5);
  REQUIRE(b < a);
}


*/
