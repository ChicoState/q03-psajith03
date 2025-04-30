/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest: public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// normal length secret
TEST(GuesserTest, normal_length_secret) {
  Guesser guesser("hello");
  EXPECT_EQ(guesser.remaining(), 3);
}

// long secret
TEST(GuesserTest, long_secret) {
  Guesser guesser("long_secret_that_should_be_truncated");
  EXPECT_EQ(guesser.remaining(), 3);
}

// exact match
TEST(GuesserTest, exact_match) {
  Guesser guesser("secret");
  EXPECT_TRUE(guesser.match("secret"));
  EXPECT_EQ(guesser.remaining(), 3);
}

// close match (distance <= 2)
TEST(GuesserTest, close_match) {
  Guesser guesser("secret");
  EXPECT_FALSE(guesser.match("secre"));
  EXPECT_EQ(guesser.remaining(), 2);
  EXPECT_FALSE(guesser.match("secre"));
  EXPECT_EQ(guesser.remaining(), 1);
  EXPECT_FALSE(guesser.match("secre"));
  EXPECT_EQ(guesser.remaining(), 0);
}

// far match (distance > 2)
TEST(GuesserTest, far_match) {
  Guesser guesser("secret");
  EXPECT_FALSE(guesser.match("xyzabc"));
  EXPECT_EQ(guesser.remaining(), 3);
}

// remaining guesses countdown
TEST(GuesserTest, remaining_guesses_countdown) {
  Guesser guesser("secret");
  EXPECT_EQ(guesser.remaining(), 3);
  EXPECT_FALSE(guesser.match("secre"));
  EXPECT_EQ(guesser.remaining(), 2);
  EXPECT_FALSE(guesser.match("secre"));
  EXPECT_EQ(guesser.remaining(), 1);
  EXPECT_FALSE(guesser.match("secre"));
  EXPECT_EQ(guesser.remaining(), 0);
}

// locked after three wrong guesses
TEST(GuesserTest, locked_after_three_wrong_guesses) {
  Guesser guesser("secret");
  EXPECT_FALSE(guesser.match("secre"));
  EXPECT_FALSE(guesser.match("secre"));
  EXPECT_FALSE(guesser.match("secre"));
  EXPECT_FALSE(guesser.match("secret")); 
}

// distance calculation with different length strings
TEST(GuesserTest, distance_different_lengths_strings) {
  Guesser guesser("short");
  EXPECT_FALSE(guesser.match("shortest"));
  EXPECT_EQ(guesser.remaining(), 3); 
}

// reset after correct guess
TEST(GuesserTest, reset_after_correct_guess) {
  Guesser guesser("secret");
  EXPECT_FALSE(guesser.match("secre"));
  EXPECT_EQ(guesser.remaining(), 2);
  EXPECT_TRUE(guesser.match("secret"));
  EXPECT_EQ(guesser.remaining(), 2); 
}

// guess longer than secret
TEST(GuesserTest, guess_longer_than_secret) {
  Guesser guesser("short");
  EXPECT_FALSE(guesser.match("this_is_much_longer_than_the_secret"));
  EXPECT_EQ(guesser.remaining(), 3);
}

// locked state behavior
TEST(GuesserTest, locked_state_behavior) {
  Guesser guesser("secret");
  EXPECT_FALSE(guesser.match("xyzabc"));
  EXPECT_FALSE(guesser.match("secret"));
  EXPECT_EQ(guesser.remaining(), 3);
}

// length difference exceeding secret length
TEST(GuesserTest, length_difference_exceeding_secret_length) {
  Guesser guesser("a");
  EXPECT_FALSE(guesser.match("abcdefghijklmnopqrstuvwxyz"));
  EXPECT_EQ(guesser.remaining(), 2);
}
