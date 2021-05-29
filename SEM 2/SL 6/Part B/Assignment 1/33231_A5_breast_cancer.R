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

# Dataset : Breast cancer Dataset
# a.Create data subsets

# get working directory
getwd()

#View data in dataset
#library("readxl")
df_bc=read.csv2("BreastCancerWc.csv",header = T, sep = ',')
View(df_bc)
#naming the columns
names(df_bc) <- c("ID","CT","cellSize", "cellShape","MA","ECellSize","BN","BC","NN","Mit","Class")
View(df_bc)

# Creating Subsets
subset1 <- df_bc[c(1:100),c(1,2,4,6,10)]
subset1
subset2 <- df_bc[c(1:50),c(1,2,5,7)]
subset2

# b. Merge Data
#Read the datasets
dataA=read.csv2("BreastCancerWc.csv",header = T, sep = ',')
dataB=read.csv2("BreastCancerWc.csv",header = T, sep = ',')
# Dimensions of both datasets
dim(dataA)
dim(dataB)
# merging the datasets
newAB=rbind(dataA,dataB)
# Dimensions of new dataset created after merging
dim(newAB)

# c. Sort Data
# sort by CT(X5)
newdata=read.csv2("BreastCancerWc.csv",header = T, sep = ',')
attach(newdata)
newdata[1:30,]
sort(X5)
detach(newdata)

# d. Transposing Data
subset1 <- subset1[order(subset1$`CT`),]
t(subset1)

# e. Melting Data to long format
library(reshape)
subset2 <- df_bc[c(10:20),c(1,2,5,7)]
melt1 <- melt(subset2,id <- c("ID","MA"))
melt1
melt1 <- melt1[order(melt1$`ID`,melt1$`MA`),]
melt1

# f. Casting data to wide format
cast1 <- cast(melt1,`ID` + `MA`~ variable,value.var = "value")
cast1
