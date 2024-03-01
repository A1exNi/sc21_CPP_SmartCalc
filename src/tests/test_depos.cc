#include <gtest/gtest.h>

#include <vector>

#include "../model/deposcalc.h"

TEST(DeposCalc, depos_calc) {
  s21::InputDataDeposCalc inputData;
  inputData.amountStr = "5000000.0";
  inputData.taxRateStr = "13.0";
  inputData.interestRateStr = "5.0";
  std::string freqPay = "every day";
  inputData.freqPayStr = &freqPay;
  tm startDate{};
  startDate.tm_year = 2023 - 1900;
  startDate.tm_mon = 10 - 1;
  startDate.tm_mday = 18;
  inputData.tmStartDate = startDate;
  tm endDate{};
  endDate.tm_year = 2028 - 1900;
  endDate.tm_mon = 10 - 1;
  endDate.tm_mday = 18;
  inputData.tmEndDate = endDate;
  inputData.isCapitalization = false;
  tm replDate = startDate;
  replDate.tm_mon += 1;
  std::multimap<time_t, std::string> withdrawalReplData = {
      {mktime(&replDate), "10000"}};
  replDate.tm_mon += 1;
  withdrawalReplData.insert({mktime(&replDate), "10000"});
  replDate.tm_mon = 1;
  ++replDate.tm_year;
  withdrawalReplData.insert({mktime(&replDate), "-10000"});
  inputData.withdrawalReplData = &withdrawalReplData;
  s21::DeposCalc calc;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1252681.62);
  ASSERT_FLOAT_EQ(calc.GetTax(), 58749.59);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "every week";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1252680.82);
  ASSERT_FLOAT_EQ(calc.GetTax(), 59107.08);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "once a month";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1252680.98);
  ASSERT_FLOAT_EQ(calc.GetTax(), 59911.68);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "once a quarter";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1252681.05);
  ASSERT_FLOAT_EQ(calc.GetTax(), 65348.54);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "once in half-year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1252681.04);
  ASSERT_FLOAT_EQ(calc.GetTax(), 65348.54);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "once a year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1252681.04);
  ASSERT_FLOAT_EQ(calc.GetTax(), 65348.54);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "at the end";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1252681.04);
  ASSERT_FLOAT_EQ(calc.GetTax(), 143348.54);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);
}

TEST(DeposCalc, depos_calc2) {
  s21::InputDataDeposCalc inputData;
  inputData.amountStr = "5000000.0";
  tm startDate{};
  startDate.tm_year = 2023 - 1900;
  startDate.tm_mon = 10 - 1;
  startDate.tm_mday = 18;
  inputData.tmStartDate = startDate;
  tm endDate{};
  endDate.tm_year = 2028 - 1900;
  endDate.tm_mon = 10 - 1;
  endDate.tm_mday = 18;
  inputData.tmEndDate = endDate;
  inputData.taxRateStr = "13.0";
  inputData.interestRateStr = "5.0";
  std::string freqPay = "every day";
  inputData.freqPayStr = &freqPay;
  inputData.isCapitalization = true;
  tm replDate = startDate;
  replDate.tm_mon += 1;
  std::multimap<time_t, std::string> withdrawalReplData = {
      {mktime(&replDate), "10000"}};
  replDate.tm_mon += 1;
  withdrawalReplData.insert({mktime(&replDate), "10000"});
  replDate.tm_mon = 1;
  ++replDate.tm_year;
  withdrawalReplData.insert({mktime(&replDate), "-10000"});
  inputData.withdrawalReplData = &withdrawalReplData;
  s21::DeposCalc calc;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1423088.48);
  ASSERT_FLOAT_EQ(calc.GetTax(), 80869.41);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6433088.48);

  freqPay = "every week";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1422428.66);
  ASSERT_FLOAT_EQ(calc.GetTax(), 81147.32);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6432428.66);

  freqPay = "once a month";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1419855.05);
  ASSERT_FLOAT_EQ(calc.GetTax(), 81632.96);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6429855.05);

  freqPay = "once a quarter";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1413234.51);
  ASSERT_FLOAT_EQ(calc.GetTax(), 86220.49);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6423234.51);

  freqPay = "once in half-year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1403449.55);
  ASSERT_FLOAT_EQ(calc.GetTax(), 84948.44);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6413449.55);

  freqPay = "once a year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1384390.68);
  ASSERT_FLOAT_EQ(calc.GetTax(), 82470.79);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6394390.68);
}

TEST(DeposCalc, depos_calc3) {
  s21::InputDataDeposCalc inputData;
  inputData.amountStr = "5000000.0";
  tm startDate{};
  startDate.tm_year = 2023 - 1900;
  startDate.tm_mon = 10 - 1;
  startDate.tm_mday = 31;
  inputData.tmStartDate = startDate;
  tm endDate{};
  endDate.tm_year = 2029 - 1900;
  endDate.tm_mon = 4 - 1;
  endDate.tm_mday = 30;
  inputData.tmEndDate = endDate;
  inputData.taxRateStr = "13.0";
  inputData.interestRateStr = "5.0";
  std::string freqPay = "every day";
  inputData.freqPayStr = &freqPay;
  inputData.isCapitalization = false;
  tm replDate = startDate;
  replDate.tm_mday = 18;
  replDate.tm_mon += 1;
  std::multimap<time_t, std::string> withdrawalReplData = {
      {mktime(&replDate), "10000"}};
  replDate.tm_mon += 1;
  withdrawalReplData.insert({mktime(&replDate), "10000"});
  replDate.tm_mon = 1;
  ++replDate.tm_year;
  withdrawalReplData.insert({mktime(&replDate), "-10000"});
  inputData.withdrawalReplData = &withdrawalReplData;
  s21::DeposCalc calc;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1376781.35);
  ASSERT_FLOAT_EQ(calc.GetTax(), 65333.81);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "every week";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1376780.38);
  ASSERT_FLOAT_EQ(calc.GetTax(), 65335.78);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "once a month";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1376780.56);
  ASSERT_FLOAT_EQ(calc.GetTax(), 65343.32);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "once a quarter";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1376780.66);
  ASSERT_FLOAT_EQ(calc.GetTax(), 65436.66);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "once in half-year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1376780.64);
  ASSERT_FLOAT_EQ(calc.GetTax(), 65436.66);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "once a year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1376780.63);
  ASSERT_FLOAT_EQ(calc.GetTax(), 65347.68);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);

  freqPay = "at the end";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1376780.64);
  ASSERT_FLOAT_EQ(calc.GetTax(), 159481.48);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5010000);
}

TEST(DeposCalc, depos_calc4) {
  s21::InputDataDeposCalc inputData;
  inputData.amountStr = "5000000.0";
  tm startDate{};
  startDate.tm_year = 2023 - 1900;
  startDate.tm_mon = 10 - 1;
  startDate.tm_mday = 31;
  inputData.tmStartDate = startDate;
  tm endDate{};
  endDate.tm_year = 2029 - 1900;
  endDate.tm_mon = 4 - 1;
  endDate.tm_mday = 30;
  inputData.tmEndDate = endDate;
  inputData.taxRateStr = "13.0";
  inputData.interestRateStr = "5.0";
  std::string freqPay = "every day";
  inputData.freqPayStr = &freqPay;
  inputData.isCapitalization = true;
  tm replDate = startDate;
  replDate.tm_mday = 18;
  replDate.tm_mon += 1;
  std::multimap<time_t, std::string> withdrawalReplData = {
      {mktime(&replDate), "10000"}};
  replDate.tm_mon += 1;
  withdrawalReplData.insert({mktime(&replDate), "10000"});
  replDate.tm_mon = 1;
  ++replDate.tm_year;
  withdrawalReplData.insert({mktime(&replDate), "-10000"});
  inputData.withdrawalReplData = &withdrawalReplData;
  s21::DeposCalc calc;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1584417.53);
  ASSERT_FLOAT_EQ(calc.GetTax(), 89034.36);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6594417.53);

  freqPay = "every week";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1583674.44);
  ASSERT_FLOAT_EQ(calc.GetTax(), 88822.09);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6593674.44);

  freqPay = "once a month";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1580777.53);
  ASSERT_FLOAT_EQ(calc.GetTax(), 87857.43);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6590777.53);

  freqPay = "once a quarter";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1573324.59);
  ASSERT_FLOAT_EQ(calc.GetTax(), 87532.20);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6583324.59);

  freqPay = "once in half-year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1562312.00);
  ASSERT_FLOAT_EQ(calc.GetTax(), 86100.56);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6572312.00);

  freqPay = "once a year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 1542782.35);
  ASSERT_FLOAT_EQ(calc.GetTax(), 83561.71);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 6552782.35);
}

TEST(DeposCalc, depos_calc5) {
  s21::InputDataDeposCalc inputData;
  inputData.amountStr = "5000000.0";
  tm startDate{};
  startDate.tm_year = 2023 - 1900;
  startDate.tm_mon = 12 - 1;
  startDate.tm_mday = 31;
  inputData.tmStartDate = startDate;
  tm endDate{};
  endDate.tm_year = 2033 - 1900;
  endDate.tm_mon = 7 - 1;
  endDate.tm_mday = 31;
  inputData.tmEndDate = endDate;
  inputData.taxRateStr = "13.0";
  inputData.interestRateStr = "5.0";
  std::string freqPay = "every day";
  inputData.freqPayStr = &freqPay;
  inputData.isCapitalization = false;
  std::multimap<time_t, std::string> withdrawalReplData;
  inputData.withdrawalReplData = &withdrawalReplData;
  s21::DeposCalc calc;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395201.74);
  ASSERT_FLOAT_EQ(calc.GetTax(), 116999.56);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "every week";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395205.17);
  ASSERT_FLOAT_EQ(calc.GetTax(), 116555.97);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "once a month";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395205.62);
  ASSERT_FLOAT_EQ(calc.GetTax(), 116376.73);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "once a quarter";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395205.55);
  ASSERT_FLOAT_EQ(calc.GetTax(), 116376.72);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "once in half-year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395205.48);
  ASSERT_FLOAT_EQ(calc.GetTax(), 119626.71);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "once a year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395205.48);
  ASSERT_FLOAT_EQ(calc.GetTax(), 117000.00);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "at the end";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395205.48);
  ASSERT_FLOAT_EQ(calc.GetTax(), 291876.71);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);
}

TEST(DeposCalc, depos_calc6) {
  s21::InputDataDeposCalc inputData;
  inputData.amountStr = "5000000.0";
  tm startDate{};
  startDate.tm_year = 2023 - 1900;
  startDate.tm_mon = 12 - 1;
  startDate.tm_mday = 31;
  inputData.tmStartDate = startDate;
  tm endDate{};
  endDate.tm_year = 2033 - 1900;
  endDate.tm_mon = 7 - 1;
  endDate.tm_mday = 31;
  inputData.tmEndDate = endDate;
  inputData.taxRateStr = "13.0";
  inputData.interestRateStr = "5.0";
  std::string freqPay = "every day";
  inputData.freqPayStr = &freqPay;
  inputData.isCapitalization = true;
  std::multimap<time_t, std::string> withdrawalReplData;
  inputData.withdrawalReplData = &withdrawalReplData;
  s21::DeposCalc calc;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 3072362.86);
  ASSERT_FLOAT_EQ(calc.GetTax(), 204407.17);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 8072362.86);

  freqPay = "every week";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 3070776.25);
  ASSERT_FLOAT_EQ(calc.GetTax(), 204200.91);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 8070776.25);

  freqPay = "once a month";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 3064593.65);
  ASSERT_FLOAT_EQ(calc.GetTax(), 203397.17);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 8064593.65);

  freqPay = "once a quarter";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 3048832.08);
  ASSERT_FLOAT_EQ(calc.GetTax(), 201348.17);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 8048832.08);

  freqPay = "once in half-year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 3025561.11);
  ASSERT_FLOAT_EQ(calc.GetTax(), 201572.94);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 8025561.11);

  freqPay = "once a year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2981902.44);
  ASSERT_FLOAT_EQ(calc.GetTax(), 192647.32);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 7981902.44);
}

TEST(DeposCalc, depos_calc7) {
  s21::InputDataDeposCalc inputData;
  inputData.amountStr = "5000000.0";
  tm startDate{};
  startDate.tm_year = 2024 - 1900;
  startDate.tm_mon = 2 - 1;
  startDate.tm_mday = 29;
  inputData.tmStartDate = startDate;
  tm endDate{};
  endDate.tm_year = 2033 - 1900;
  endDate.tm_mon = 9 - 1;
  endDate.tm_mday = 29;
  inputData.tmEndDate = endDate;
  inputData.taxRateStr = "13.0";
  inputData.interestRateStr = "5.0";
  std::string freqPay = "every day";
  inputData.freqPayStr = &freqPay;
  inputData.isCapitalization = false;
  std::multimap<time_t, std::string> withdrawalReplData;
  inputData.withdrawalReplData = &withdrawalReplData;
  s21::DeposCalc calc;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395313.94);
  ASSERT_FLOAT_EQ(calc.GetTax(), 116390.81);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "every week";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395317.46);
  ASSERT_FLOAT_EQ(calc.GetTax(), 116391.27);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "once a month";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395317.91);
  ASSERT_FLOAT_EQ(calc.GetTax(), 116391.33);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "once a quarter";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395317.80);
  ASSERT_FLOAT_EQ(calc.GetTax(), 116391.31);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "once in half-year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395317.76);
  ASSERT_FLOAT_EQ(calc.GetTax(), 119730.11);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "once a year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395317.76);
  ASSERT_FLOAT_EQ(calc.GetTax(), 135891.31);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);

  freqPay = "at the end";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2395317.76);
  ASSERT_FLOAT_EQ(calc.GetTax(), 291891.31);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 5000000);
}

TEST(DeposCalc, depos_calc8) {
  s21::InputDataDeposCalc inputData;
  inputData.amountStr = "5000000.0";
  tm startDate{};
  startDate.tm_year = 2024 - 1900;
  startDate.tm_mon = 2 - 1;
  startDate.tm_mday = 29;
  inputData.tmStartDate = startDate;
  tm endDate{};
  endDate.tm_year = 2033 - 1900;
  endDate.tm_mon = 9 - 1;
  endDate.tm_mday = 29;
  inputData.tmEndDate = endDate;
  inputData.taxRateStr = "13.0";
  inputData.interestRateStr = "5.0";
  std::string freqPay = "every day";
  inputData.freqPayStr = &freqPay;
  inputData.isCapitalization = true;
  std::multimap<time_t, std::string> withdrawalReplData;
  inputData.withdrawalReplData = &withdrawalReplData;
  s21::DeposCalc calc;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 3072543.81);
  ASSERT_FLOAT_EQ(calc.GetTax(), 204430.70);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 8072543.81);

  freqPay = "every week";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 3070957.30);
  ASSERT_FLOAT_EQ(calc.GetTax(), 204224.45);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 8070957.30);

  freqPay = "once a month";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 3064773.95);
  ASSERT_FLOAT_EQ(calc.GetTax(), 203420.61);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 8064773.95);

  freqPay = "once a quarter";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 3048991.95);
  ASSERT_FLOAT_EQ(calc.GetTax(), 201368.95);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 8048991.95);

  freqPay = "once in half-year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 3025691.86);
  ASSERT_FLOAT_EQ(calc.GetTax(), 201678.74);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 8025691.86);

  freqPay = "once a year";
  inputData.freqPayStr = &freqPay;
  calc.DeposCalcResult(inputData);
  ASSERT_FLOAT_EQ(calc.GetInterest(), 2982072.95);
  ASSERT_FLOAT_EQ(calc.GetTax(), 212169.48);
  ASSERT_FLOAT_EQ(calc.GetDepAmount(), 7982072.95);
}

TEST(DeposCalc, amount_error) {
  std::string amountStr = "adsf";
  s21::DeposCalc calc;
  calc.CheckAmountError(amountStr);
  ASSERT_EQ(calc.GetError(), s21::AMOUNT);
}