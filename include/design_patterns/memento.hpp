#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include "data_structures/data_buffer.hpp"

class Memento {
public:

    // Alias pour simplifier l'utilisation des snapshots.
    using Snapshot = DataBuffer;

    virtual ~Memento() = default;

    // Sauvegarde l'état actuel dans un snapshot (DataBuffer).
    Snapshot save() const {
        Snapshot snapshot;

        // Appelle la méthode protégée pour remplir le snapshot.
        _saveToSnapshot(snapshot);

        // Retourne le snapshot rempli.
        return snapshot;
    }

    // Recharge l'état à partir d'un snapshot (DataBuffer).
    void load(const Snapshot& snapshot) {

        // Copie mutable pour permettre les modifications.
        Snapshot mutableSnapshot = snapshot;

        // Appelle la méthode protégée pour recharger l'état.
        _loadFromSnapshot(mutableSnapshot);
    }

protected:

    // Méthode virtuelle pure pour définir comment sauvegarder l'état dans un snapshot.
    virtual void _saveToSnapshot(Snapshot& snapshotToFill) const = 0;

    // Méthode virtuelle pure pour définir comment recharger l'état depuis un snapshot.
    virtual void _loadFromSnapshot(Snapshot& snapshot) = 0;
};

#endif