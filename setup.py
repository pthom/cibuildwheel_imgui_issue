import sys

try:
    from skbuild import setup
except ImportError:
    print(
        "Please update pip, you need pip 10 or greater,\n"
        " or you need to install the PEP 518 requirements in pyproject.toml yourself",
        file=sys.stderr,
    )
    raise


setup(
    name="mylib",
    version="0.0.1",
    description="mylib, example of bindings with skbuild and litgen",
    long_description="...",
    author="Pascal Thomet",
    author_email="pthomet@gmail.com",
    url="https://github.com/pthom/litgen",
    packages=(["mylib"]),
    package_dir={"": "bindings"},
    cmake_install_dir="bindings/mylib",
    # include_package_data=True,
    package_data={"mylib": ["py.typed", "*.pyi"]},
    extras_require={"test": ["pytest"]},
    python_requires=">=3.6",
    install_requires=[],
)
