#include <QCoreApplication>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
  QCoreApplication a(argc, argv);

  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  return a.exec();
}
