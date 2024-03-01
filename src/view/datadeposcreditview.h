#ifndef CPP3_SMARTCALC_V2_0_2_SRC_VIEW_DATADEPOSCREDITVIEW_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_VIEW_DATADEPOSCREDITVIEW_H_

#include <map>

namespace s21 {

struct OutputDataCreditView {
  std::string amountStr;
  std::string timeStr;
  std::string rateStr;
  char yearsMonthsDays;
  bool annuity;
};

struct OutputDataDeposView {
  std::string amountStr;
  std::string taxRateStr;
  std::string interestRateStr;
  std::string freqPayStr;
  tm tmStartDate;
  tm tmEndDate;
  bool isCapitalization;
  std::multimap<time_t, std::string> withdrawalReplData;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_VIEW_DATADEPOSCREDITVIEW_H_