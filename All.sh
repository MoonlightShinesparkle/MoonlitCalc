zsh Build.sh

printf "%s" "Upload to pico? (y/n): "
read Response

if [[ "$Response" == "y" ]]; then
	echo "Uploading..."
	zsh Load.sh
fi