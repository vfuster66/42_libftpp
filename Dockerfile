FROM ubuntu:latest

# Installation des dépendances nécessaires
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    cmake \
    git \
    make \
    valgrind \
    gdb \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Création du répertoire de travail
WORKDIR /app

# Copie des fichiers du projet
COPY . .

# Configuration de l'environnement
ENV CC=gcc
ENV CXX=g++