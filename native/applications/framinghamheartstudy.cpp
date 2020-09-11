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

    auto context = SEALContext::Create(parms);

    KeyGenerator keygen(context);
    auto public_key = keygen.public_key();
    auto secret_key = keygen.secret_key();

    Encryptor encryptor(context, public_key);
    Decryptor decryptor(context, secret_key);
    Evaluator evaluator(context);

    double scale = pow(2.0, 40);

    CKKSEncoder encoder(context);

    // Encodes the variables before Encryption
    vector<double> variables{ 26, 100, 70, 100, 72, 180 };
    vector<Plaintext> plain_var;
    for (auto val : variables)
    {
        Plaintext p;
        encoder.encode(val, scale, p);
        plain_var.emplace_back(move(p));
    }

    // Encrypts the variables before Computation
    vector<Ciphertext> cipher_var;
    for (const auto& p : plain_var)
    {
        Ciphertext c;
        encryptor.encrypt(p, c);
        cipher_var.emplace_back(move(c));
    }

    // Create vector for the weighted values
    vector<double> xweights{ 0.072, 0.013, -0.029, 0.008, -0.053, 0.021 };
    vector<Plaintext> plain_xweights;
    for (auto wt : xweights)
    {
        Plaintext p;
        encoder.encode(wt, scale, p);
        plain_xweights.emplace_back(move(p));
    }

    // Multiply weights and encrypted variables in place
    for (auto i = 0; i < cipher_var.size(); i++)
    {
        evaluator.multiply_plain_inplace(cipher_var[i], plain_xweights[i]);
        evaluator.rescale_to_next_inplace(cipher_var[i]);
    }

    // Add values in cipher
    Ciphertext cipher_var_result;
    evaluator.add_many(cipher_var, cipher_var_result);

    // Taylor series coefficients
    vector<double> taylor_coef{ 1.0 / 4, 1.0 / 48, 1.0 / 480, 17.0 / 80640, 31 / 1451520 };

    // Decrypt Results
    Plaintext plain_result;
    decryptor.decrypt(cipher_var_result, plain_result);

    // Decode Results
    vector<double> final_result;
    encoder.decode(plain_result, final_result);
    cout << "Result: " << final_result[0] << endl;
    cout << "True result: " << inner_product(variables.cbegin(), variables.cend(), xweights.cbegin(), 0.0) << endl;

    // final_result[0] is the value of x
    double x = final_result[0];

    /* Create the constant and calculate for likelihood of Heart Attack using
       Taylor series approximation and Exact equation.
    */
    double constant = 1.0 / 2;
    
    double result = constant + (x * taylor_coef[0]) - (taylor_coef[1] * pow(x, 3)) + (taylor_coef[2] * pow(x, 5)) - (taylor_coef[3] * pow(x, 7));
    double true_result = exp(x) / (exp(x) + 1);
    cout << result << endl;
    cout << true_result << endl;

}
