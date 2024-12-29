echo "Deleting build/"
rm -rf build/
echo "Creating build/"
cmake -S . -B build/
