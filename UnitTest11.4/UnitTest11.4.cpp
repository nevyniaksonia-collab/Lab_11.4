#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_11.4/Lab_11.4.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestFileProcessing
{
    TEST_CLASS(UnitTestFileProcessing)
    {
    public:

        TEST_METHOD(Test_ProcessFile_RemovesShortWords)
        {
            // === 1. Створюємо тестовий файл ===
            string fileName = "test1.txt";
            {
                ofstream f(fileName);
                f << "hello hi abcde no yes\n";
                f << "short longword mid\n";
            }

            // === 2. Викликаємо функцію ===
            int removed = ProcessFile(fileName, 4);
            // Видаляються слова: hi, no, yes, mid  (4 слова)

            Assert::AreEqual(4, removed);

            // === 3. Перевіряємо результуючий файл ===
            ifstream f(fileName);
            string line;
            getline(f, line);
            Assert::AreEqual(string("hello abcde"), line);

            getline(f, line);
            Assert::AreEqual(string("short longword"), line);
        }


        TEST_METHOD(Test_ProcessFile_EmptyLines)
        {
            string fileName = "test2.txt";
            {
                ofstream f(fileName);
                f << "\n";
                f << "one two three\n";
                f << "\n";
            }

            int removed = ProcessFile(fileName, 4);
            // Видаляються: one, two (2 слова)

            Assert::AreEqual(2, removed);

            ifstream f2(fileName);
            string line;
            getline(f2, line);

            // Залишається тільки "three"
            Assert::AreEqual(string("three"), line);
        }


        TEST_METHOD(Test_ProcessFile_NoShortWords)
        {
            string fileName = "test3.txt";
            {
                ofstream f(fileName);
                f << "alpha beta gamma\n";
            }

            int removed = ProcessFile(fileName, 3); // нічого не видаляється

            Assert::AreEqual(0, removed);

            ifstream f(fileName);
            string line;
            getline(f, line);

            Assert::AreEqual(string("alpha beta gamma"), line);
        }
    };
}
