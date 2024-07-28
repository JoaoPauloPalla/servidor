#!/bin/bash

#HOST= "servidor" #"192.168.1.5"
SUBJECT_CA="/C=BR/ST=MinasGerais/L=Cataguases/O=MakeBeer/OU=CA/CN=Servidor"
SUBJECT_SERVER="/C=BR/ST=MinasGerais/L=Cataguases/O=MakeBeer/OU=Server/CN=Servidor"
SUBJECT_CLIENT_SERVICE="/C=BR/ST=MinasGerais/L=Cataguases/O=MakeBeer/OU=ESP/CN=Servidor"
SUBJECT_CLIENT_MANAGER="/C=BR/ST=MinasGerais/L=Cataguases/O=MakeBeer/OU=FRONT/CN=Servidor"

function generate_CA () {
   echo "$SUBJECT_CA"
   openssl req -x509 -nodes -sha256 -newkey rsa:2048 -subj "$SUBJECT_CA"  -days 365 -keyout ca.key -out ca.crt
}

function generate_server () {
   echo "$SUBJECT_SERVER"
   openssl req -nodes -sha256 -new -subj "$SUBJECT_SERVER" -keyout server.key -out server.csr
   openssl x509 -req -sha256 -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 365
}

function generate_client_service() {
   echo "$SUBJECT_CLIENT_SERVICE"
   openssl req -new -nodes -sha256 -subj "$SUBJECT_CLIENT_SERVICE" -out service.csr -keyout service.key 
   openssl x509 -req -sha256 -in service.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out service.crt -days 365
}

function generate_client_manager() {
   echo "$SUBJECT_CLIENT_MANAGER"
   openssl req -new -nodes -sha256 -subj "$SUBJECT_CLIENT_MANAGER" -out manager.csr -keyout manager.key 
   openssl x509 -req -sha256 -in manager.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out manager.crt -days 365
}


function generate_certificado_ca() {
   echo "$SUBJECT_CA"
   #openssl req -x509 -nodes -sha256 -newkey rsa:2048 -subj "$SUBJECT_CA"  -days 365 -keyout ca.key -out ca.crt
   openssl genrsa -out ca.key 2048
   openssl req -new -x509 -days 1826 -subj "$SUBJECT_CA" -key ca.key -out ca.crt
}

function generate_certificado_servidor(){
   echo "$SUBJECT_SERVER"
   openssl genrsa -out server.key 2048
   openssl req -new -subj "$SUBJECT_SERVER" -out server.csr -key server.key
   openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 360 
}


# generate_CA
# generate_server
# generate_client_service
# generate_client_manager
generate_certificado_ca
generate_certificado_servidor

