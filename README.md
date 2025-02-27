# 🛠️ LD_PRELOAD SSH Klein Dylan et Dupont Lelian 3SI3

## 📌 Description
Ce projet utilise **LD_PRELOAD** pour intercepter les identifiants SSH (`username/password`) lorsqu'un utilisateur se connecte à un serveur **OpenSSH**.  
Les credentials sont ensuite envoyés à un **serveur de Commande & Contrôle (C2)**.

---

## 🌍 **Architecture du Projet**
| **Machine** | **Rôle** | **Adresse IP** |
|------------|----------|----------------|
| **Attaquante (Kali Linux)** | Serveur C2 | `192.168.3.131` |
| **Serveur SSH (Debian)** | SSH infecté par LD_PRELOAD | `192.168.3.133` |
| **Victime (Kali Linux)** | Se connecte en SSH au serveur infecté | `192.168.3.134` |

---

# 🚀 **Installation & Exécution**

## **1️⃣ Configuration du Serveur C2 (Attaquant - `192.168.3.131`)**
### 📌 **Installation**
```bash
sudo apt update && sudo apt install -y gcc netcat
