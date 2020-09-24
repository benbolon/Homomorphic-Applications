# Homomorphic-Applications
A collection of applications utilizing Homomorphic Encryption.

# Contents
- [Introduction](#introduction)
  - [Homomorphic Encryption](#homomorphic-encryption)
  - [Microsoft SEAL](#microsoft-seal-1)
- [Installing Microsoft SEAL](#installing-microsoft-seal)
- [SEAL Applications]
  - [Framingham Heart Study]
  
# Introduction

## Homomorphic Encryption
Homomorphic Encryption (HE) is a tool that will change the way in which people encrypt and interact with data 
or, at least, that is what it could be. This form of encryption allows one to encrypt data and run computations
on that encrypted data without the need for decryption. With traditional encryption methods, when performing data 
analysis it is necessary to decrypt the ciphertext before computing over the dataset. This dynamic risks the 
security of the data in question. Properly implementing HE can eliminate this gap in security. SO, why are we not
implementing this tool more widely? Three general reasons:

1. Computations over encrypted datasets are inefficient.
2. Difficulty or inability to verify results.
3. Difficulty in constructing meaningful applications utilizing HE.

Solving these issues is necessary to the adoption of this tool, but these are not easy problems to solve. SO, is
it worth it? Personally, I believe it is. Databreaches are an increasing occurance and the implementation of this
tool has the ability to mitigate data theft and loss in variety of industries. The most relevant being the medical
industry, which must properly secure senstive data and maintain an ability to interact with it in a meaningful way.

## Microsoft SEAL
Place Holder

# Installing Microsoft SEAL
Place Holder

# SEAL Applications

## Framingham Heart Study
The Framingham Heart Study followed roughly 5000 patients over the course of many decades starting in 1948, and again added another cohort of 5000, which consisted of the spouses and children of those in the original study and then similarly added another 5000 in the years proceeding. The aim of this study was to develop a method of predicting the likelihood of Cardiovascular Disease (CVD). Although many health-related variables were recorded during observation in the study, six were used in what would become a logistic regression model for calculating the likelihood of heart attack in men. These predictive variables included age, height, weight, systolic blood pressure (SBP), diastolic blood pressure (DBP), and cholesterol levels (CHL). These are the values, which will be encrypted prior to computation. The predictive model is described below:

Equation 1 – x = 0.072∙Age+0.013∙SBP-0.029∙DBP+0.008∙CHL-0.053∙height+0.021∙weight

Where x is used in the below logistic regression:

Equation 2 – P(x) =  e^x/(e^x+1)

Equation 2 used in this application is common throughout statistical analysis and machine learning techniques. For the application, this equation must be converted into an approximation portrayed below as a truncated Taylor series:

Equation 3 – P(x) = 1/2+1/4∙x-1/48∙x^3+1/480∙x^5-17/80640∙x^7+O(x^11)

Author's Note: Another great example of using the above equations in Microsoft SEAL is featured in the Manual for "Using Homomorphic Encryption for Bioinformatics". This is an excellent source of indepth information and examples on the use of Microsoft SEAL. I would recommend anyone who is interested in learning more about SEAL and HE to consult this document. Keep in mind, however, that it uses an earlier version of SEAL.






  
