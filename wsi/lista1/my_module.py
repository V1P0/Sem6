from distutils.core import setup, Extension

def main():
    setup(name="puzzle15",
          version="1.0.0",
          description="Python module for solving 15 puzzle",
          author="Mateusz Jończak 261691",
          ext_modules=[Extension("puzzle15", ["my_module.cpp", "fifteen.cpp"])])

if __name__ == "__main__":
    main()
