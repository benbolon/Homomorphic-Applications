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

  
