# Waterfall Distribution Table

A waterfall distribution table allows you to see how much cash gets split at each row of the internal rate of return being greater than the inputted hurdle rate. This algorithm uses fixed-point iteration to calculate the IRR and then uses a vector to store all points where the cash split is needed. If the next rate of return is still less than the IRR in its sharing row, the cash split will be calculated as the current cash split minus the previous cash splits in that row.

# Running Example
![alt](https://github.com/marscolony2040/WaterfallDist/blob/main/img_run.png)
