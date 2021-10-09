<script>
   $(document).ready(function() {
     $head = $('#header');
     $head.prepend('<img src=\"cat.jpg\" style=\"float: right;width: 150px;z-index: 289;\"/>')
   });
</script>
<div><img src="cat.jpg" width="180px" align="right"></div>

# VE482 Lab3
# <span style="font-size:0.6em;"> Weili Shi 519370910011  Oct 7, 2021</span>
## 2. Working with source code

### 2.1 `rsync`

```sh
# installing rsync on Minix3
pkginstall rsync
man rsync
# create an copy of /usr/src into the directory /usr/src_orig
cp -r /usr/src /usr/src_orig
#Create an exact copy of the Minix 3 directory /usr/src into your Linux system
rsync -avz -e "ssh -p 2222" root@192.168.213.126:/usr/src_orig ~/exact_copy

```

### 2.2 `diff` , `patch`

```sh
man diff
man patch
#edit files
echo 111 > /usr/src/file
echo 222 > /usr/src_orig/file
# create a patch in Minix3
cd /usr/src
diff -rc /usr/src_orig /usr/src > patch
# retrieve the patch
rsync -avz -e "ssh -p 2222" root@192.168.213.126:/usr/src/patch ~/patch
# applying the patch
patch -p3 /usr/src/file < patch
# revert the patch
patch -RE -p3 < patch

```

### 2.4 Basic git

![Git_1](./git_1.png)

![git_2](git_2.png)

## 3. Scripting and regex

### 3.1 AQI and sed

```sh
curl "https://aqicn.org/?city=Shanghai&widgetscript&size=large&id=52b39d71decf07.20261781" 2> /dev/null | sed -rn 's/.*title=\\.*\">([0-9]{1,3}).*hdrt.*10px.*>([-]?[0-9]{1,3})<.*/AQ: \1 Temp: \2 ºC/p'
```

### 3.2 IP and awk

```sh
ifconfig | awk -e '{for(i=1;i<=NF;i++){ if($i=="inet"){print $(i+1)} } }'
```

