from cryptography import x509
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization

def get_modulus_from_private_key(private_key_path):
    with open(private_key_path, 'rb') as key_file:
        private_key = serialization.load_pem_private_key(
            key_file.read(),
            password=None,
            backend=default_backend()
        )
        modulus = private_key.public_key().public_numbers().n
        return modulus

def check_certificate_chain(root_key_path, intermediate_key_path, leaf_key_path):
    root_modulus = get_modulus_from_private_key(root_key_path)
    intermediate_modulus = get_modulus_from_private_key(intermediate_key_path)
    leaf_modulus = get_modulus_from_private_key(leaf_key_path)

    root_cert = x509.load_pem_x509_certificate(open('root.crt').read().encode(), default_backend())
    intermediate_cert = x509.load_pem_x509_certificate(open('dev_team.crt').read().encode(), default_backend())
    leaf_cert = x509.load_pem_x509_certificate(open('app.crt').read().encode(), default_backend())

    # Check if the leaf certificate is signed by the intermediate certificate
    try:
        default_backend().ciphers.x509.ASN1Integer.intermediate_modulus(leaf_cert, intermediate_cert)
        print("Leaf certificate is signed by the intermediate certificate. 🟩")
    except:
        print("Leaf certificate is not signed by the intermediate certificate.:🟥")

    # Check if the intermediate certificate is signed by the root certificate
    try:
        default_backend().ciphers.x509.ASN1Integer.intermediate_modulus(intermediate_cert, root_cert)
        print("Intermediate certificate is signed by the root certificate.🟩")
    except:
        print("Intermediate certificate is not signed by the root certificate.🟥")

    # Check if the private key moduli match the public key moduli in the certificates
    if root_modulus == root_cert.public_key().public_numbers().n:
        print("Root certificate public key modulus matches the root private key modulus.🟩")
    else:
        print("Root certificate public key modulus does not match the root private key modulus.🟥")

    if intermediate_modulus == intermediate_cert.public_key().public_numbers().n:
        print("Intermediate certificate public key modulus matches the intermediate private key modulus.🟩")
    else:
        print("Intermediate certificate public key modulus does not match the intermediate private key modulus.🟥")

    if leaf_modulus == leaf_cert.public_key().public_numbers().n:
        print("Leaf certificate public key modulus matches the leaf private key modulus.🟩")
    else:
        print("Leaf certificate public key modulus does not match the leaf private key modulus.🟥")

if __name__ == "__main__":
    root_private_key_path = "root.key"
    intermediate_private_key_path = "dev_team.key"
    leaf_private_key_path = "app.key"

    check_certificate_chain(root_private_key_path, intermediate_private_key_path, leaf_private_key_path)

# ROOT
#  EG
#  Cairo
#  Smart Village
#  Hossam

