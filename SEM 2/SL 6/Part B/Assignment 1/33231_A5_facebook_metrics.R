# SL-6
# Assignment 5 : Perform the following operations using R/Python
# a. Create data subsets
# b. Merge Data
# c. Sort Data
# d. Transposing Data
# e. Melting Data to long format
# f. Casting data to wide format
# Roll No : 33231
# Batch : L 10

#-----------------------------------------------------------------------------------------------------

# Dataset : Facebook metrics dataset


setwd("/home/jing/prajakta/TE\ IT/SEM\ 2/SL\ 6/R")

d = read.csv2("dataset_Facebook.csv")
dim(d) #to show the dimensions of dataset
nrow(d) #to show no of rows in dataset 
ncol(d) #to show np of columns in dataset

head(d) #to see first 6 records
tail(d) #to see last 6 records

#creating subsets
sub = d[c('comment', 'like', 'share')]
head(sub)
write.csv(sub, 'facebook-sub.csv')

subset1 = subset(sub, comment > 50)

#merging dataset
dataA = read.csv2("dataset_Facebook.csv")
dataB = read.csv2("dataset_Facebook.csv")
newAB = rbind(dataA, dataB)
dim(newAB)

#sorting the dataset
x = sub[order(-d$share),]

#transposing the dataset
trans = t(sub)

#melting the dataset
install.packages("reshape")
library(reshape)
melt(data = sub, id.vars = "comment")

# casting the dataset
s1 = d[c('Post.Month', 'Post.Hour', 'Paid')]
head(s1)
cast(s1, Post.Hour ~ Post.Month, mean, value = 'Paid')
