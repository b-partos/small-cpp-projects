# Secure HTTP GET with libcurl

## Certificate file
This example uses https and requires a certificate bundle to be present-
libcurl uses the bundle to verify the target site.

The file was downloaded from the [CURL documentation site](https://curl.se/docs/caextract.html).

## Parameters
The compiled executable requires a config file to be located in the location it is executed in.
The `config.txt` in the repository serves as an example.

The config allows the user to specify cookies that may be used for authentication.
