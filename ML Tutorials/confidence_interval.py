import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
sns.set_theme()
from scipy import stats

def confidence_interval(data, confidence_level, distribution = "t-distribution"):
    mean = np.mean(data)
    # standard error of mean
    sem = stats.sem(data)
    confidence_level = confidence_level/100 # to convert to decimal format
    degrees_of_freedom = len(data) - 1
    cumulative_probability = (1 + confidence_level) / 2
    if distribution == "t-distribution":
        critical_value = stats.t.ppf(cumulative_probability, degrees_of_freedom)
    elif distribution == "normal":
        critical_value = stats.norm.ppf(cumulative_probability)
    else:
        raise ValueError("Unsupported distribution. Choose 't-distribution' or 'normal'.")
    margin_of_error = critical_value * sem
    lower = mean - margin_of_error
    upper = mean + margin_of_error
    return float(round(lower, 2)), float(round(upper, 2))

if __name__ == "__main__":
        data = np.array([10, 12, 14, 16, 18, 20, 22])

        ci_normal = confidence_interval(data, 95, distribution="normal")
        ci_t_distribution = confidence_interval(data, 95, distribution="t-distribution")
        #ci_other = confidence_interval(data, 99, distribution="other") # willraise ValueError

        # Print results
        print("Confidence Interval using Normal Distribution:", ci_normal)
        print("Confidence Interval using T-Distribution:", ci_t_distribution)
        #print("Result for Unsupported Distribution:", ci_other)
