
echo -e "Update of TOC..."
python3 Tools/generateTOC.py "README.md"
echo -e "TOC updated !"
#Update repo
git add .
git commit -am "$1"
branch=$(git rev-parse --abbrev-ref HEAD)
git push origin $branch
