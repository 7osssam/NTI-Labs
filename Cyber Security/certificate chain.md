certificate chaining with OpenSSL, ROOT -> DEV TEAM -> APP.

### 1. Generating the Root Certificate (ROOT):

```bash
# Generate a private key for the root certificate
openssl genpkey -algorithm RSA -out root.key

# Generate a self-signed root certificate
openssl req -new -key root.key -x509 -days 365 -out root.crt
```

### 2. Generating the Intermediate Certificate for DEV TEAM:

```bash
# Generate a private key for the DEV TEAM certificate
openssl genpkey -algorithm RSA -out dev_team.key

# Generate a Certificate Signing Request (CSR) for the DEV TEAM certificate
openssl req -new -key dev_team.key -out dev_team.csr

# Sign the CSR with the ROOT private key to create the DEV TEAM certificate
openssl x509 -req -in dev_team.csr -CA root.crt -CAkey root.key -CAcreateserial -out dev_team.crt -days 365
```

### 3. Generating the Leaf Certificate for APP:

```bash
# Generate a private key for the APP certificate
openssl genpkey -algorithm RSA -out app.key

# Generate a Certificate Signing Request (CSR) for the APP certificate
openssl req -new -key app.key -out app.csr

# Sign the CSR with the DEV TEAM private key to create the APP certificate
openssl x509 -req -in app.csr -CA dev_team.crt -CAkey dev_team.key -CAcreateserial -out app.crt -days 365
```

Now, you should have a valid certificate chain: ROOT -> DEV TEAM -> APP.

To verify:

```bash
openssl verify -CAfile root.crt -untrusted dev_team.crt app.crt
```
