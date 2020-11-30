# Homomorphic-Applications
A collection of applications utilizing Homomorphic Encryption.

# Contents
- [Introduction](#introduction)
  - [Homomorphic Encryption](#homomorphic-encryption)
- [Installing Microsoft SEAL](#installing-microsoft-seal)
  - [Microsoft SEAL](#microsoft-seal-1)
  - [Downloading Microsoft SEAL](#downloading-microsoft-seal)
  - [Constructing the SEAL Coding Environment](#constructing-the-seal-coding-environment)
- [SEAL Applications](#seal-applications)
  - [Framingham Heart Study](#framingham-heart-study)
  
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
3. Expertise necessary to construct meaningful applications utilizing HE is rare.

Solving these issues is necessary to the adoption of this tool, but these are not easy problems to solve, which begs
the question is it worth it? Personally, I believe it is. Databreaches are an increasing occurance and the implementation
of this tool has the ability to mitigate data theft and loss in a variety of industries. The most relevant being the medical
industry, which must properly secure senstive data and maintain an ability to interact with it in a meaningful way. **It is
therefore the case that this repository seeks to assist in solving *PROBLEM 3* by providing an understanding of HE and its proper utilization.** 

# Installing Microsoft SEAL

## Microsoft SEAL

SEAL is a set of libraries created by Microsoft, which allows one to, and I use this term loosely, *easily* construct applications utilizing HE. 

## Downloading Microsoft SEAL

Using the program “Git Bash”, we can clone the Microsoft SEAL GitHub repository using the command “git clone https://github.com/microsoft/SEAL.git” (this url is subject to change for later releases of SEAL). Following this command, you will now have a file “SEAL” containing the necessary libraries. The final step to ensuring that all essential files have been downloaded is to open file “C:/…/SEAL/SEAL.sln” using Visual Studio, or similar IDE, and build the SEAL project file located in the folder “native”. If the build runs successfully without errors then all required tools for building in SEAL have been downloaded correctly and it is now possible to construct the coding environment for future projects.

## Constructing the SEAL Coding Environment
Going forward, I will be using Microsoft's Visual Studio: To construct a SEAL coding environment, one must create a new C++ project and link this project logically to the SEAL encryption libraries. The most straight forward method for accomplishing this is creating a new “Empty Project” and then adjusting the properties of this new project. One can find project properties, by right clicking the project within the Visual Studio IDE. Once in properties the user should input the address for the SEAL source code in “Additional Include Directories” below the “C++” tab. Most often the source code file will be in the directory “C:\..\SEAL\native\src”. While in the “C++” tab, be sure that the C++ language being used is “ISO C++ 17 Standard”. Next, within the “Linker” tab add the file path “C:\..\SEAL\lib\$(Platform)\$(Configuration)” to “Additional Library Directories”. Finally, in “Input”, also under the “Linkage” tab, add “seal.lib;” to “Additional Dependencies”. In order to ensure that all necessary directories have been included, the user can add a blank “.cpp” file under the project tab. Following this, the user should type the code “#include “seal/seal.h””. If Visual Studio recognizes this header file then the environment is suitable for further coding.

# SEAL Applications

## Framingham Heart Study
The Framingham Heart Study followed roughly 5000 patients over the course of many decades starting in 1948, and again added another cohort of 5000, which consisted of the spouses and children of those in the original study and then similarly added another 5000 in the years proceeding. The aim of this study was to develop a method of predicting the likelihood of Cardiovascular Disease (CVD). Although many health-related variables were recorded during observation in the study, six were used in what would become a logistic regression model for calculating the likelihood of heart attack in men. These predictive variables included age, height, weight, systolic blood pressure (SBP), diastolic blood pressure (DBP), and cholesterol levels (CHL). These are the values, which will be encrypted prior to computation. The predictive model is described below:

Equation 1 – x = 0.072∙Age+0.013∙SBP-0.029∙DBP+0.008∙CHL-0.053∙height+0.021∙weight

Where x is used in the below logistic regression:

Equation 2 – P(x) =  e^x/(e^x+1)

Equation 2 used in this application is common throughout statistical analysis and machine learning techniques. For the application, this equation must be converted into an approximation portrayed below as a truncated Taylor series:

Equation 3 – P(x) = 1/2+1/4∙x-1/48∙x^3+1/480∙x^5-17/80640∙x^7+O(x^11)

Author's Note: Another great example of using the above equations in Microsoft SEAL is featured in the "Manual for Using Homomorphic Encryption for Bioinformatics". This is an excellent source of indepth information and examples on the use of Microsoft SEAL. I would recommend anyone who is interested in learning more about SEAL and HE to consult this document. Keep in mind, however, that it uses an earlier version of SEAL.






  
