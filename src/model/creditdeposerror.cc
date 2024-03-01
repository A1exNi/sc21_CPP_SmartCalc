#include "creditdeposerror.h"

namespace s21 {

void CreditDeposError::CheckAmountError(std::string amountStr) {
  int count = 0;
  if (amountStr.length() == 0) error = AMOUNT;
  for (auto ch = amountStr.begin(); ch != amountStr.end() && error == NO;
       ++ch) {
    if (*ch == '.' || *ch == ',') {
      ++ch;
      while (ch != amountStr.end() && error == NO) {
        if (*ch >= '0' && *ch <= '9') {
          ++count;
          if (count > 2) error = AMOUNT;
        } else {
          error = AMOUNT;
        }
        ++ch;
      }
      --ch;
    } else if (*ch < '0' || *ch > '9') {
      error = AMOUNT;
    }
  }
  if (error == NO) {
    try {
      std::stod(amountStr);
    } catch (...) {
      error = AMOUNT;
    }
  }
}

void CreditDeposError::CheckTimeError(std::string timeStr,
                                      char yearsMonthsDays) {
  int count = 0;
  if (timeStr.length() == 0) error = TIME;
  for (auto ch = timeStr.begin(); ch != timeStr.end() && error == NO; ++ch) {
    if (*ch < '0' || *ch > '9')
      error = TIME;
    else
      ++count;
    if (yearsMonthsDays == 'y' && count > 2)
      error = TIME;
    else if (yearsMonthsDays == 'm' && count > 3)
      error = TIME;
  }
  if (error == NO) {
    int time = std::stoi(timeStr);
    if (yearsMonthsDays == 'y' && (time < 1 || time > 50)) error = TIME;
    if (yearsMonthsDays == 'm' && (time < 1 || time > 600)) error = TIME;
    if (yearsMonthsDays == 'd' && (time < 1 || time > 18250)) error = TIME;
  }
}

void CreditDeposError::CheckRateError(std::string rateStr) {
  int count = 0;
  if (rateStr.length() == 0) error = RATE;
  for (auto ch = rateStr.begin(); ch != rateStr.end() && error == NO; ++ch) {
    if (*ch == '.' || *ch == ',') {
      ++ch;
      while (ch != rateStr.end() && error == NO) {
        if (*ch >= '0' && *ch <= '9') {
          ++count;
          if (count > 2) error = RATE;
        } else {
          error = RATE;
        }
        ++ch;
      }
      --ch;
    } else if (*ch < '0' || *ch > '9') {
      error = RATE;
    }
    if (error == NO) {
      try {
        double rate = std::stod(rateStr);
        if (rate < 1 || rate > 999.0) error = RATE;
      } catch (...) {
        error = RATE;
      }
    }
  }
}

void CreditDeposError::Reset() { error = NO; }

}  // namespace s21