#include "seal/seal.h"
#include <iostream>

using namespace std;
using namespace seal;

int main()
{
    EncryptionParameters parms(scheme_type::CKKS);

    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, { 60, 40, 40, 60 }));

    /*
    We use a scale of 2^40 to allow for 20 bits of precision before the decimal point
    and 10-20 bits of precision after. Note that the we use 40-bit primes above.
    */
    double scale = pow(2.0, 40);

    auto context = SEALContext::Create(parms);

    // Generates Public Key, Secret Key, and Relinearization Keys, respectfully.
    KeyGenerator keygen(context);
    auto public_key = keygen.public_key();
    auto secret_key = keygen.secret_key();
    auto relin_keys = keygen.relin_keys_local();

    // Applies variable:context and above keys to generate Encryption and Decryption classes.
    Encryptor encryptor(context, public_key);
    Decryptor decryptor(context, secret_key);
    Evaluator evaluator(context);

    CKKSEncoder encoder(context);

    // Encodes the patient data before Encryption.
    vector<double> variables{ 26, 100, 70, 100, 72, 180 };
    vector<Plaintext> plain_var;
    for (auto val : variables)
    {
        Plaintext p;
        encoder.encode(val, scale, p);
        plain_var.emplace_back(move(p));
    }

    // Encrypts the variables before Computation.
    vector<Ciphertext> cipher_var;
    for (const auto& p : plain_var)
    {
        Ciphertext c;
        encryptor.encrypt(p, c);
        cipher_var.emplace_back(move(c));
    }

    // Create vector for the weighted values for the calculation of x.
    vector<double> xweights{ 0.072, 0.013, -0.029, 0.008, -0.053, 0.021 };
    vector<Plaintext> plain_xweights;
    for (auto wt : xweights)
    {
        Plaintext p;
        encoder.encode(wt, scale, p);
        plain_xweights.emplace_back(move(p));
    }

    // Multiply weights and encrypted variables in place.
    for (auto i = 0; i < cipher_var.size(); i++)
    {
        evaluator.multiply_plain_inplace(cipher_var[i], plain_xweights[i]);
        evaluator.rescale_to_next_inplace(cipher_var[i]);
    }

    // Add values in cipher to calculate for x.
    Ciphertext cipher_var_result;
    evaluator.add_many(cipher_var, cipher_var_result);

    // Create vector of coefficients corresponding to the Taylor series approx described in the README.
    vector<double> taylor_coef{ 1.0 / 4, -1.0 / 48, 1.0 / 480, -17.0 / 80640, 31 / 1451520 };
    vector<Plaintext> plain_taylor_coef;
    for (auto wt : taylor_coef)
    {
        Plaintext p;
        encoder.encode(wt, scale, p);
        plain_taylor_coef.emplace_back(move(p));
    }

    // Compute for the Taylor series. This is admittedly messy and I need to make some adjustments.
    Ciphertext taylor_result;
    evaluator.multiply_plain(cipher_var_result, plain_taylor_coef[0], taylor_result);
    for (int i = 1; i < 4; ++i)
    {
        Ciphertext powerofx, prod;
        // Correct efficieny problem resulting from integer interation (???)
        evaluator.exponentiate(cipher_var_result, 2 * i + 1, relin_keys, powerofx);
        evaluator.multiply_plain(powerofx, plain_taylor_coef[i], prod);
        evaluator.add(taylor_result, prod, taylor_result);
    }
    Plaintext taylor_constant;
    encoder.encode(scale, taylor_constant);
    evaluator.add_plain(taylor_result, taylor_constant, taylor_result);

    // Decrypt 
    Plaintext plain_taylor_result;
    decryptor.decrypt(taylor_result, plain_taylor_result);

    // Decrypt Encrypted Taylor Series Results
    vector<double> final_taylor_result;
    encoder.decode(plain_taylor_result, final_taylor_result);

    cout << "Result for encrypted T-series: " << final_taylor_result[0] << endl;

    /*
    Plaintext plain_result;
    decryptor.decrypt(cipher_var_result, plain_result);

     Create the constant and calculate for likelihood of Heart Attack using
       Taylor series approximation and Exact equation.
    
    double constant = 1.0 / 2;

    double result = constant + (x * taylor_coef[0]) - (taylor_coef[1] * pow(x, 3)) + (taylor_coef[2] * pow(x, 5)) - (taylor_coef[3] * pow(x, 7));
    double true_result = exp(x) / (exp(x) + 1);
    cout << "Result for T-series: " << result << endl;
    cout << true_result << endl;
    */

}
