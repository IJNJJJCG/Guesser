/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST_F(GuesserTest, TestConstructor)
{
	Guesser g("secret");
	EXPECT_TRUE(g.match("secret"));
}

TEST_F(GuesserTest, TestMatch)
{
	Guesser g("secret");
	EXPECT_TRUE(g.match("secret"));
	EXPECT_FALSE(g.match("secreT"));
}

TEST_F(GuesserTest, TestDistance)
{
	Guesser g("secret");
	EXPECT_EQ(g.distance("secret"), 0);
	EXPECT_EQ(g.distance("secreT"), 1);
	EXPECT_EQ(g.distance("secre"), 1);
	EXPECT_EQ(g.distance("ssecrett"), 1);
	EXPECT_EQ(g.distance("seeecrettt"), 2);
	EXPECT_EQ(g.distance("secrrrretttt"), 3);
}

TEST_F(GuesserTest, TestLocking)
{
	Guesser g("secret");
	EXPECT_FALSE(g.match("secreT"));
	EXPECT_FALSE(g.match("Secret"));
	EXPECT_FALSE(g.match("sECREt"));
	EXPECT_TRUE(g.match("secret"));
}

TEST_F(GuesserTest, TestTruncation)
{
	Guesser g("This is a very long secret that should be truncated at 32 characters");
	EXPECT_TRUE(g.match("This is a very long secret that should be truncated at 32 characters"));
	EXPECT_TRUE(g.match("This is a very long secret that should be truncated at 32 charact"));
	EXPECT_FALSE(g.match("This is a very long secret that should be truncated at 32 characters!"));
}

TEST_F(GuesserTest, TestBruteForce)
{
	Guesser g("secret");
	EXPECT_FALSE(g.match("sECREt"));
	EXPECT_FALSE(g.match("sECREt"));
	EXPECT_FALSE(g.match("sECREt"));
	EXPECT_FALSE(g.match("secret"));
}

TEST_F(GuesserTest, TestBruteForceWithDistance)
{
	Guesser g("secret");
	EXPECT_FALSE(g.match("sECREt"));
	EXPECT_FALSE(g.match("st"));
	EXPECT_FALSE(g.match("ECRE"));
	EXPECT_TRUE(g.match("secret"));
}

TEST_F(GuesserTest, TestBruteForceWithDistanceAndRemaining)
{
	Guesser g("secret");
	EXPECT_FALSE(g.match("sECREt"));
	EXPECT_FALSE(g.match("st"));
	EXPECT_FALSE(g.match("ECRE"));
	EXPECT_FALSE(g.match("secret"));
	EXPECT_TRUE(g.match("secret"));
}

TEST_F(GuesserTest, TestBruteForceWithDistanceAndRemainingAndLocking)
{
	Guesser g("secret");
	EXPECT_FALSE(g.match("sECREt"));
	EXPECT_FALSE(g.match("st"));
	EXPECT_FALSE(g.match("ECRE"));
	EXPECT_FALSE(g.match("secret"));
	EXPECT_TRUE(g.match(""));
	EXPECT_FALSE(g.match(""));
}