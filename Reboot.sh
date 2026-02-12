printf "%s" "Reboot pico? (y/n): "
read Response

if [[ "$Response" == "y" ]]; then
	echo "Rebooting..."
	picotool reboot -F
	echo "Estabishing USB connection"
	sleep 2
	zsh Debug.sh
fi