#include <gtest/gtest.h>
#include "hashtable.h"

/* tests for constructor */

TEST(constructor, Copy_Constructor_Not_Empty) {
    HashTable a;
    a.insert("a", {"vfgr", 42});
    a.insert("b", {"Eric", 13});
    a.insert("c", {"Erlo", 42});

    HashTable b(a);

    EXPECT_EQ(b.size(), 3);
    EXPECT_TRUE(b.contains("a"));
    EXPECT_TRUE(b.contains("b"));
    EXPECT_TRUE(b.contains("c"));
}

TEST(constructor, Copy_Constructor_Empty) {
    HashTable a;
    HashTable b(a);

    EXPECT_EQ(b.size(), a.size());
}

/* tests for operator= */

TEST(operators, Assignment_Constructor_Not_Empty) {
    HashTable a;
    a.insert("a", {"vfgr", 42});
    a.insert("b", {"Eric", 13});
    a.insert("c", {"Erlo", 42});

    HashTable b;
    b = a;

    EXPECT_EQ(b.size(), a.size());
    EXPECT_TRUE(b.contains("a"));
    EXPECT_TRUE(b.contains("b"));
    EXPECT_TRUE(b.contains("c"));
}

TEST(operators, Assignment_Constructor_Empty) {
    HashTable a, b;

    b = a;

    EXPECT_EQ(b.size(), a.size());
}

/* tests for operator[] */

TEST(operators, Square_Brackets_When_Element_Existed) {
    HashTable a;
    a.insert("a", {"vfgr", 42});

    Value result = a["a"];
    EXPECT_TRUE(result.name == "vfgr");
    EXPECT_TRUE(result.age == 42);
    EXPECT_EQ(a.size(), 1);
}

TEST(operators, Square_Brackets_When_Element_Not_Existed) {
    HashTable a;

    a.insert("a", {"vfgr", 42});
    a.insert("b", {"Eric", 13});

    Value result = a["d"];

    EXPECT_TRUE(result.name.empty());
    EXPECT_EQ(result.age, 0);
    EXPECT_EQ(a.size(), 3);
}

/* tests for operator== and != */

TEST(operators, Equals_And_Not_Equals) {
    HashTable a;
    a.insert("a", {"vfgr", 42});
    a.insert("b", {"Eric", 13});
    a.insert("c", {"Erlo", 42});
    a.insert("d", {"Avgust", 33});

    HashTable b;
    b.insert("d", {"Avgust", 33});
    b.insert("c", {"Erlo", 42});
    b.insert("b", {"Eric", 13});
    b.insert("a", {"vfgr", 42});

    /* a == b */
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    a.insert("e", {"vfgr", 42});
    b.insert("e", {"Eric", 13});

    /* a != b */
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);

    a.erase("e");
    b.erase("e");

    /* a == b */
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

/* tests for size */

TEST(size, Empty) {
    HashTable a;
    EXPECT_EQ(a.size(), 0);
}

TEST(size, Not_Empty) {
    HashTable a;
    a.insert("a", {"vfgr", 42});
    a.insert("b", {"Eric", 13});
    a.insert("c", {"Erlo", 42});

    EXPECT_EQ(a.size(), 3);
}

/* tests for swap */

TEST(swap, Swap_Correct) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", {"vfgr", 42});
    a.insert("b", {"Eric", 13});
    a.insert("c", {"Erlo", 42});

    HashTable b;
    b.insert("a", {"vfgr", 42});
    b.insert("b", {"Eric", 13});

    a.swap(b);

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 3);
    EXPECT_TRUE(a["a"] == elements[0]);
    EXPECT_TRUE(a["b"] == elements[1]);
    EXPECT_TRUE(b["a"] == elements[0]);
    EXPECT_TRUE(b["b"] == elements[1]);
    EXPECT_TRUE(b["c"] == elements[2]);
}

/* tests for clear */

TEST(clear, Not_Empty) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    a.clear();

    EXPECT_EQ(a.size(), 0);
    EXPECT_FALSE(a.contains("a"));
    EXPECT_FALSE(a.contains("b"));
    EXPECT_FALSE(a.contains("c"));
}

TEST(clear, Empty) {
    HashTable a;

    a.clear();

    EXPECT_EQ(a.size(), 0);
}

/* tests for erase */

TEST(erase, Not_Empty_Find_Element) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    EXPECT_TRUE(a.erase("a"));
    EXPECT_EQ(a.size(), 2);
    EXPECT_TRUE(a.contains("b"));
    EXPECT_TRUE(a.contains("c"));
    EXPECT_FALSE(a.contains("a"));
}

TEST(erase, Not_Empty_Not_Find_Element) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    EXPECT_FALSE(a.erase("d"));
    EXPECT_EQ(a.size(), 3);
    EXPECT_TRUE(a.contains("b"));
    EXPECT_TRUE(a.contains("c"));
    EXPECT_TRUE(a.contains("a"));
}

TEST(erase, Empty_Not_Find_Element) {
    HashTable b;

    EXPECT_FALSE(b.erase("a"));
}

TEST(erase, Delete_Two_Element_In_List) {
    HashTable a;
    a.insert("first", {"f", 32});
    a.insert("second", {"f", 32});
    a.insert("third", {"f", 32});

    EXPECT_TRUE(a.erase("second"));
    EXPECT_TRUE(a.contains("first"));
    EXPECT_TRUE(a.contains("third"));
}

/* tests for contains */

TEST(contains, Find) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);

    EXPECT_TRUE(a.contains("a"));
    EXPECT_TRUE(a.contains("b"));
    EXPECT_TRUE(a.contains("c"));
}

TEST(contains, Not_Find) {
    HashTable a;
    Value elements[3];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);

    EXPECT_FALSE(a.contains("c"));
}

/* tests for insert */

TEST(insert, Element_Exist) {
    HashTable a;
    a.insert("a", Value("reg"));
    a.insert("a", Value("vdf"));

    EXPECT_EQ(a.size(), 1);
    EXPECT_TRUE(a["a"].name == "vdf");
}

TEST(insert, Element_Not_Exist) {
    HashTable a;
    a.insert("a", Value("reg"));
    a.insert("b", Value("vdf"));

    EXPECT_EQ(a.size(), 2);
    EXPECT_TRUE(a["a"].name == "reg");
    EXPECT_TRUE(a["b"].name == "vdf");
}

/* tests for at */

TEST(at, Element_Exist) {
    HashTable a;
    a.insert("a", {"sasc", 42});

    Value result = a.at("a");

    EXPECT_TRUE(result == Value("sasc", 42));
}

TEST(at, Element_Not_Exist) {
    HashTable a;
    a.insert("a", {"sasc", 42});

    ASSERT_THROW(a.at("b"), std::out_of_range);
}

TEST(at, Const_Value) {
    HashTable a;
    a.insert("a", {"sasc", 42});

    const Value& result = a.at("a");

    EXPECT_TRUE(result == Value("sasc", 42));
}

/* tests for empty */

TEST(empty, Empty_For_Empty) {
    HashTable a;
    EXPECT_TRUE(a.empty());
}

TEST(empty, Empty_For_Not_Empty) {
    HashTable a;

    a.insert("a", {"vfgr", 42});
    a.insert("b",  {"Eric", 13});

    EXPECT_FALSE(a.empty());
}

/* tests for resize */

TEST(resize, Correct_Work_Resize) {
    HashTable a;
    Value elements[10];
    elements[0] = {"vfgr", 42};
    elements[1] = {"Eric", 13};
    elements[2] = {"Erlo", 42};
    elements[3] = {"Avgust", 33};
    elements[4] = {"Jfwkesf", 134};
    elements[5] = {"erte", 13};
    elements[6] = {"jty", 42};
    elements[7] = {"gdas", 33};
    elements[8] = {"vfg", 134};
    elements[9] = {"erfge", 13};

    a.insert("a", elements[0]);
    a.insert("b", elements[1]);
    a.insert("c", elements[2]);
    a.insert("d", elements[3]);
    a.insert("e", elements[4]);
    a.insert("f", elements[5]);
    a.insert("g", elements[6]);
    a.insert("h", elements[7]);
    a.insert("t", elements[8]);
    a.insert("y", elements[9]);

    EXPECT_TRUE(a.contains("a"));
    EXPECT_TRUE(a.contains("b"));
    EXPECT_TRUE(a.contains("c"));
    EXPECT_TRUE(a.contains("d"));
    EXPECT_TRUE(a.contains("e"));
    EXPECT_TRUE(a.contains("f"));
    EXPECT_TRUE(a.contains("g"));
    EXPECT_TRUE(a.contains("h"));
    EXPECT_TRUE(a.contains("t"));
    EXPECT_TRUE(a.contains("y"));
    EXPECT_EQ(a.size(), 10);
}