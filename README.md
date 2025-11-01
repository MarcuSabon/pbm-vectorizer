# 🖼️ Vector is on Time

## 📖 Description

This project was developed in **C** with an execution script written in **shell (sh)**.
The goal is to create a **black and white PBM image vectorizer**, capable of converting bitmap (PBM) images into vector paths (EPS) using **Bézier curve approximations** (order 2 or 3) or **segment simplification**.

The execution script provides an **interactive command-line interface**, allowing the user to:

* Select a `.pbm` file
* Choose the vectorization mode (`bezier2`, `bezier3`, or `segment simplification`)
* Set a precision threshold `d`
* Automatically visualize the result in an EPS viewer (`gv`)

---

## ✨ Main Features

* 🧩 Reading and analyzing black & white PBM images
* 📈 Conversion into Bézier vector paths (2nd or 3rd order)
* 🧮 Adjustable threshold `d` for simplification precision
* 🗂️ Automatic output management in `dossier_eps/`
* 💬 Simple and interactive shell interface
* 🎨 Direct visualization with `gv`

---

## ⚙️ Installation

### 🔧 Dependencies

Make sure the following tools are installed on your system:

| Tool          | Purpose                | Installation Command               |
| ------------- | ---------------------- | ---------------------------------- |
| `gcc`         | Compiling the C code   | `sudo apt install build-essential` |
| `make`        | Compilation automation | *(included with build-essential)*  |
| `gv`          | EPS file viewer        | `sudo apt install gv`              |
| `bash` / `sh` | Script execution       | *(default on Linux/macOS)*         |

---

## 🚀 Usage

### 1️⃣ Compilation

The `exec.sh` script handles compilation automatically, but you can also compile manually:

```bash
make
```

To grant execution rights to the script:

```bash
chmod 700 exec.sh
```

### 2️⃣ Launch the Program

Run the interactive script:

```bash
./exec.sh
```

You’ll see something like this:

```
###########################################
#                                         #
#     Welcome to Vector is on Time        #
#                                         #
#         Please choose a PBM file        #
#                                         #
###########################################
```

### 3️⃣ Selecting a PBM File

Place your `.pbm` files inside the `dossier_pbm/` folder.
Then enter the filename (e.g. `cat.pbm`).

### 4️⃣ Choosing the Vectorization Mode

You can choose:

* `bezier2` → 2nd-order Bézier curves
* `bezier3` → 3rd-order Bézier curves
* `segment simplification` → Linear simplification

The program generates a `.eps` file in `dossier_eps/` and automatically opens it using `gv`.

---

## 🧪 Performance Testing

You can test performance across different files using the `test.sh` script:

```bash
chmod 700 test.sh
./test.sh
```

---

## 👨‍💻 Authors

Developed in C by **Sabon Marcus** and **Stien Emilio**
Original version: **2023**
Updated and published on GitHub: **2025**
