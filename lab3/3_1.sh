# !/bin/bash
curl "https://aqicn.org/?city=Shanghai&widgetscript&size=large&id=52b39d71decf07.20261781" 2> /dev/null | sed -rn 's/.*title=\\.*\">([0-9]{1,3}).*hdrt.*10px.*>([-]?[0-9]{1,3})<.*/AQ: \1 Temp: \2 ºC/p'
