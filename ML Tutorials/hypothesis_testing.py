import numpy as np
from scipy import stats
import math

def hypothesis_test(data, h_mean, alpha = 0.05, axis=0, side = "two-sided"):

    """Performs a one-sample t-test to determine if the sample data significantly differs from a hypothesized population mean.

      Args:
          data: The sample data.
          h_mean: The hypothesized population mean.
          alpha: The significance level (default: 0.05).
          axis: The axis along which to compute the mean (default: 0).
          side: The alternative hypothesis ('two-sided', 'less', or 'greater').

      Returns:
          None
      """

    if not side in ["two-sided", "less", "greater"]:
        raise ValueError("Allow value for tails: two-sided, less, greater")

    t_statistic, p_value = stats.ttest_1samp(data, popmean = h_mean, axis = axis, nan_policy="omit", alternative = side)

    print(f"Calculated t-statistic: {t_statistic}")
    print(f"P-value: {p_value}")
    print(f"Significance level at {alpha}")

    if p_value < alpha:
        print("Reject Null Hypothesis")
    else:
        print("Fail to reject the null hypothesis")


if __name__ == "__main__":
    data = [2.5, 2.7, 3.1, 3.2, 2.8]
    h_mean = 3.0
    hypothesis_test(data, h_mean, axis = 0, side="greater")
