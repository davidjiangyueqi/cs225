#!/bin/sh
# This script was generated using Makeself 2.3.0

ORIG_UMASK=`umask`
if test "n" = n; then
    umask 077
fi

CRCsum="2383252901"
MD5="504cc3554c55627f2cb71c41967fb601"
TMPROOT=${TMPDIR:=/tmp}
USER_PWD="$PWD"; export USER_PWD

label="Extracting gotw-03"
script="echo"
scriptargs="The initial files can be found in the newly created directory: gotw-03"
licensetxt=""
helpheader=''
targetdir="gotw-03"
filesizes="3029"
keep="y"
nooverwrite="n"
quiet="n"
nodiskspace="n"

print_cmd_arg=""
if type printf > /dev/null; then
    print_cmd="printf"
elif test -x /usr/ucb/echo; then
    print_cmd="/usr/ucb/echo"
else
    print_cmd="echo"
fi

unset CDPATH

MS_Printf()
{
    $print_cmd $print_cmd_arg "$1"
}

MS_PrintLicense()
{
  if test x"$licensetxt" != x; then
    echo "$licensetxt"
    while true
    do
      MS_Printf "Please type y to accept, n otherwise: "
      read yn
      if test x"$yn" = xn; then
        keep=n
	eval $finish; exit 1
        break;
      elif test x"$yn" = xy; then
        break;
      fi
    done
  fi
}

MS_diskspace()
{
	(
	if test -d /usr/xpg4/bin; then
		PATH=/usr/xpg4/bin:$PATH
	fi
	df -kP "$1" | tail -1 | awk '{ if ($4 ~ /%/) {print $3} else {print $4} }'
	)
}

MS_dd()
{
    blocks=`expr $3 / 1024`
    bytes=`expr $3 % 1024`
    dd if="$1" ibs=$2 skip=1 obs=1024 conv=sync 2> /dev/null | \
    { test $blocks -gt 0 && dd ibs=1024 obs=1024 count=$blocks ; \
      test $bytes  -gt 0 && dd ibs=1 obs=1024 count=$bytes ; } 2> /dev/null
}

MS_dd_Progress()
{
    if test x"$noprogress" = xy; then
        MS_dd $@
        return $?
    fi
    file="$1"
    offset=$2
    length=$3
    pos=0
    bsize=4194304
    while test $bsize -gt $length; do
        bsize=`expr $bsize / 4`
    done
    blocks=`expr $length / $bsize`
    bytes=`expr $length % $bsize`
    (
        dd ibs=$offset skip=1 2>/dev/null
        pos=`expr $pos \+ $bsize`
        MS_Printf "     0%% " 1>&2
        if test $blocks -gt 0; then
            while test $pos -le $length; do
                dd bs=$bsize count=1 2>/dev/null
                pcent=`expr $length / 100`
                pcent=`expr $pos / $pcent`
                if test $pcent -lt 100; then
                    MS_Printf "\b\b\b\b\b\b\b" 1>&2
                    if test $pcent -lt 10; then
                        MS_Printf "    $pcent%% " 1>&2
                    else
                        MS_Printf "   $pcent%% " 1>&2
                    fi
                fi
                pos=`expr $pos \+ $bsize`
            done
        fi
        if test $bytes -gt 0; then
            dd bs=$bytes count=1 2>/dev/null
        fi
        MS_Printf "\b\b\b\b\b\b\b" 1>&2
        MS_Printf " 100%%  " 1>&2
    ) < "$file"
}

MS_Help()
{
    cat << EOH >&2
${helpheader}Makeself version 2.3.0
 1) Getting help or info about $0 :
  $0 --help   Print this message
  $0 --info   Print embedded info : title, default target directory, embedded script ...
  $0 --lsm    Print embedded lsm entry (or no LSM)
  $0 --list   Print the list of files in the archive
  $0 --check  Checks integrity of the archive

 2) Running $0 :
  $0 [options] [--] [additional arguments to embedded script]
  with following options (in that order)
  --confirm             Ask before running embedded script
  --quiet		Do not print anything except error messages
  --noexec              Do not run embedded script
  --keep                Do not erase target directory after running
			the embedded script
  --noprogress          Do not show the progress during the decompression
  --nox11               Do not spawn an xterm
  --nochown             Do not give the extracted files to the current user
  --nodiskspace         Do not check for available disk space
  --target dir          Extract directly to a target directory
                        directory path can be either absolute or relative
  --tar arg1 [arg2 ...] Access the contents of the archive through the tar command
  --                    Following arguments will be passed to the embedded script
EOH
}

MS_Check()
{
    OLD_PATH="$PATH"
    PATH=${GUESS_MD5_PATH:-"$OLD_PATH:/bin:/usr/bin:/sbin:/usr/local/ssl/bin:/usr/local/bin:/opt/openssl/bin"}
	MD5_ARG=""
    MD5_PATH=`exec <&- 2>&-; which md5sum || command -v md5sum || type md5sum`
    test -x "$MD5_PATH" || MD5_PATH=`exec <&- 2>&-; which md5 || command -v md5 || type md5`
	test -x "$MD5_PATH" || MD5_PATH=`exec <&- 2>&-; which digest || command -v digest || type digest`
    PATH="$OLD_PATH"

    if test x"$quiet" = xn; then
		MS_Printf "Verifying archive integrity..."
    fi
    offset=`head -n 532 "$1" | wc -c | tr -d " "`
    verb=$2
    i=1
    for s in $filesizes
    do
		crc=`echo $CRCsum | cut -d" " -f$i`
		if test -x "$MD5_PATH"; then
			if test x"`basename $MD5_PATH`" = xdigest; then
				MD5_ARG="-a md5"
			fi
			md5=`echo $MD5 | cut -d" " -f$i`
			if test x"$md5" = x00000000000000000000000000000000; then
				test x"$verb" = xy && echo " $1 does not contain an embedded MD5 checksum." >&2
			else
				md5sum=`MS_dd_Progress "$1" $offset $s | eval "$MD5_PATH $MD5_ARG" | cut -b-32`;
				if test x"$md5sum" != x"$md5"; then
					echo "Error in MD5 checksums: $md5sum is different from $md5" >&2
					exit 2
				else
					test x"$verb" = xy && MS_Printf " MD5 checksums are OK." >&2
				fi
				crc="0000000000"; verb=n
			fi
		fi
		if test x"$crc" = x0000000000; then
			test x"$verb" = xy && echo " $1 does not contain a CRC checksum." >&2
		else
			sum1=`MS_dd_Progress "$1" $offset $s | CMD_ENV=xpg4 cksum | awk '{print $1}'`
			if test x"$sum1" = x"$crc"; then
				test x"$verb" = xy && MS_Printf " CRC checksums are OK." >&2
			else
				echo "Error in checksums: $sum1 is different from $crc" >&2
				exit 2;
			fi
		fi
		i=`expr $i + 1`
		offset=`expr $offset + $s`
    done
    if test x"$quiet" = xn; then
		echo " All good."
    fi
}

UnTAR()
{
    if test x"$quiet" = xn; then
		tar $1vf - 2>&1 || { echo Extraction failed. > /dev/tty; kill -15 $$; }
    else

		tar $1f - 2>&1 || { echo Extraction failed. > /dev/tty; kill -15 $$; }
    fi
}

finish=true
xterm_loop=
noprogress=n
nox11=n
copy=none
ownership=y
verbose=n

initargs="$@"

while true
do
    case "$1" in
    -h | --help)
	MS_Help
	exit 0
	;;
    -q | --quiet)
	quiet=y
	noprogress=y
	shift
	;;
    --info)
	echo Identification: "$label"
	echo Target directory: "$targetdir"
	echo Uncompressed size: 32 KB
	echo Compression: gzip
	echo Date of packaging: Wed Sep 23 15:32:15 EDT 2020
	echo Built with Makeself version 2.3.0 on darwin18
	echo Build command was: "./makeself/makeself.sh \\
    \"--notemp\" \\
    \"../../questions/gotw_03/gotw-03\" \\
    \"../../questions/gotw_03/clientFilesQuestion/gotw-03.sh\" \\
    \"Extracting gotw-03\" \\
    \"echo\" \\
    \"The initial files can be found in the newly created directory: gotw-03\""
	if test x"$script" != x; then
	    echo Script run after extraction:
	    echo "    " $script $scriptargs
	fi
	if test x"" = xcopy; then
		echo "Archive will copy itself to a temporary location"
	fi
	if test x"n" = xy; then
		echo "Root permissions required for extraction"
	fi
	if test x"y" = xy; then
	    echo "directory $targetdir is permanent"
	else
	    echo "$targetdir will be removed after extraction"
	fi
	exit 0
	;;
    --dumpconf)
	echo LABEL=\"$label\"
	echo SCRIPT=\"$script\"
	echo SCRIPTARGS=\"$scriptargs\"
	echo archdirname=\"gotw-03\"
	echo KEEP=y
	echo NOOVERWRITE=n
	echo COMPRESS=gzip
	echo filesizes=\"$filesizes\"
	echo CRCsum=\"$CRCsum\"
	echo MD5sum=\"$MD5\"
	echo OLDUSIZE=32
	echo OLDSKIP=533
	exit 0
	;;
    --lsm)
cat << EOLSM
No LSM.
EOLSM
	exit 0
	;;
    --list)
	echo Target directory: $targetdir
	offset=`head -n 532 "$0" | wc -c | tr -d " "`
	for s in $filesizes
	do
	    MS_dd "$0" $offset $s | eval "gzip -cd" | UnTAR t
	    offset=`expr $offset + $s`
	done
	exit 0
	;;
	--tar)
	offset=`head -n 532 "$0" | wc -c | tr -d " "`
	arg1="$2"
    if ! shift 2; then MS_Help; exit 1; fi
	for s in $filesizes
	do
	    MS_dd "$0" $offset $s | eval "gzip -cd" | tar "$arg1" - "$@"
	    offset=`expr $offset + $s`
	done
	exit 0
	;;
    --check)
	MS_Check "$0" y
	exit 0
	;;
    --confirm)
	verbose=y
	shift
	;;
	--noexec)
	script=""
	shift
	;;
    --keep)
	keep=y
	shift
	;;
    --target)
	keep=y
	targetdir=${2:-.}
    if ! shift 2; then MS_Help; exit 1; fi
	;;
    --noprogress)
	noprogress=y
	shift
	;;
    --nox11)
	nox11=y
	shift
	;;
    --nochown)
	ownership=n
	shift
	;;
    --nodiskspace)
	nodiskspace=y
	shift
	;;
    --xwin)
	if test "n" = n; then
		finish="echo Press Return to close this window...; read junk"
	fi
	xterm_loop=1
	shift
	;;
    --phase2)
	copy=phase2
	shift
	;;
    --)
	shift
	break ;;
    -*)
	echo Unrecognized flag : "$1" >&2
	MS_Help
	exit 1
	;;
    *)
	break ;;
    esac
done

if test x"$quiet" = xy -a x"$verbose" = xy; then
	echo Cannot be verbose and quiet at the same time. >&2
	exit 1
fi

if test x"n" = xy -a `id -u` -ne 0; then
	echo "Administrative privileges required for this archive (use su or sudo)" >&2
	exit 1	
fi

if test x"$copy" \!= xphase2; then
    MS_PrintLicense
fi

case "$copy" in
copy)
    tmpdir=$TMPROOT/makeself.$RANDOM.`date +"%y%m%d%H%M%S"`.$$
    mkdir "$tmpdir" || {
	echo "Could not create temporary directory $tmpdir" >&2
	exit 1
    }
    SCRIPT_COPY="$tmpdir/makeself"
    echo "Copying to a temporary location..." >&2
    cp "$0" "$SCRIPT_COPY"
    chmod +x "$SCRIPT_COPY"
    cd "$TMPROOT"
    exec "$SCRIPT_COPY" --phase2 -- $initargs
    ;;
phase2)
    finish="$finish ; rm -rf `dirname $0`"
    ;;
esac

if test x"$nox11" = xn; then
    if tty -s; then                 # Do we have a terminal?
	:
    else
        if test x"$DISPLAY" != x -a x"$xterm_loop" = x; then  # No, but do we have X?
            if xset q > /dev/null 2>&1; then # Check for valid DISPLAY variable
                GUESS_XTERMS="xterm gnome-terminal rxvt dtterm eterm Eterm xfce4-terminal lxterminal kvt konsole aterm terminology"
                for a in $GUESS_XTERMS; do
                    if type $a >/dev/null 2>&1; then
                        XTERM=$a
                        break
                    fi
                done
                chmod a+x $0 || echo Please add execution rights on $0
                if test `echo "$0" | cut -c1` = "/"; then # Spawn a terminal!
                    exec $XTERM -title "$label" -e "$0" --xwin "$initargs"
                else
                    exec $XTERM -title "$label" -e "./$0" --xwin "$initargs"
                fi
            fi
        fi
    fi
fi

if test x"$targetdir" = x.; then
    tmpdir="."
else
    if test x"$keep" = xy; then
	if test x"$nooverwrite" = xy && test -d "$targetdir"; then
            echo "Target directory $targetdir already exists, aborting." >&2
            exit 1
	fi
	if test x"$quiet" = xn; then
	    echo "Creating directory $targetdir" >&2
	fi
	tmpdir="$targetdir"
	dashp="-p"
    else
	tmpdir="$TMPROOT/selfgz$$$RANDOM"
	dashp=""
    fi
    mkdir $dashp $tmpdir || {
	echo 'Cannot create target directory' $tmpdir >&2
	echo 'You should try option --target dir' >&2
	eval $finish
	exit 1
    }
fi

location="`pwd`"
if test x"$SETUP_NOCHECK" != x1; then
    MS_Check "$0"
fi
offset=`head -n 532 "$0" | wc -c | tr -d " "`

if test x"$verbose" = xy; then
	MS_Printf "About to extract 32 KB in $tmpdir ... Proceed ? [Y/n] "
	read yn
	if test x"$yn" = xn; then
		eval $finish; exit 1
	fi
fi

if test x"$quiet" = xn; then
	MS_Printf "Uncompressing $label"
fi
res=3
if test x"$keep" = xn; then
    trap 'echo Signal caught, cleaning up >&2; cd $TMPROOT; /bin/rm -rf $tmpdir; eval $finish; exit 15' 1 2 3 15
fi

if test x"$nodiskspace" = xn; then
    leftspace=`MS_diskspace $tmpdir`
    if test -n "$leftspace"; then
        if test "$leftspace" -lt 32; then
            echo
            echo "Not enough space left in "`dirname $tmpdir`" ($leftspace KB) to decompress $0 (32 KB)" >&2
            echo "Use --nodiskspace option to skip this check and proceed anyway" >&2
            if test x"$keep" = xn; then
                echo "Consider setting TMPDIR to a directory with more free space."
            fi
            eval $finish; exit 1
        fi
    fi
fi

for s in $filesizes
do
    if MS_dd_Progress "$0" $offset $s | eval "gzip -cd" | ( cd "$tmpdir"; umask $ORIG_UMASK ; UnTAR xp ) 1>/dev/null; then
		if test x"$ownership" = xy; then
			(PATH=/usr/xpg4/bin:$PATH; cd "$tmpdir"; chown -R `id -u` .;  chgrp -R `id -g` .)
		fi
    else
		echo >&2
		echo "Unable to decompress $0" >&2
		eval $finish; exit 1
    fi
    offset=`expr $offset + $s`
done
if test x"$quiet" = xn; then
	echo
fi

cd "$tmpdir"
res=0
if test x"$script" != x; then
    if test x"$verbose" = x"y"; then
		MS_Printf "OK to execute: $script $scriptargs $* ? [Y/n] "
		read yn
		if test x"$yn" = x -o x"$yn" = xy -o x"$yn" = xY; then
			eval "\"$script\" $scriptargs \"\$@\""; res=$?;
		fi
    else
		eval "\"$script\" $scriptargs \"\$@\""; res=$?
    fi
    if test "$res" -ne 0; then
		test x"$verbose" = xy && echo "The program '$script' returned an error code ($res)" >&2
    fi
fi
if test x"$keep" = xn; then
    cd $TMPROOT
    /bin/rm -rf $tmpdir
fi
eval $finish; exit $res
‹ ¿¢k_í[moÛ8î×êWL½4NªØ‰ã°Û M»M·—4E_Ğ=`€–éX¨$êô’Ä8´¿ıf(J¢$Êu—d÷ ‰mqfH‡Ã™‡ÔîàÁ­—ápøt<ùy˜}÷²OU`oôtLeô†{£ñÁèŒÜAIã„EØ•ÈM÷+có%şÜ’-ëIã(>ÿ&ewà;‘˜7ßuÂğÖæÿğà uşÇûX™ÍÿèéÓÃœÿÃáxü †İüßzùÅ/sxæŠ8‰8ó,«xØ+ŒcÙÓFµ‘F,HªÏE4ç=²¬3çƒdœLòo[ıÉ‡‚o«÷†…á
Ş{Ìá½'°7ìÃ¿­ofÆ8Á_Ø97¸„à	¸A~E>ôsş+áÎ¡2wãĞc«3¤[DX¤<G¤	<{½/Üs„Ï!Û£ÕH2Ì½©Ë6•’ÚøÎlhÎVcğ±OØ ©7ÌŸ¥Ñ%6 }¹<Ş€îÌã¶ë¸"á$â<ˆooÌŸ–â;.ó@, ÁŸ¨pã	œ É°€Fóo8J°mø=„}å10˜¹	ªCá+‘¢‚Å3ø…?¾âÀ¼XÀ¥Hd¯Şs†ò‚9|Z²à+üee]z¿ÃÎ¢Äu–â+×kşŞ¸	œqøâ&Kªˆà->.™ç¡ÜŒìØ€-G	WÔÍc1CÈêêšiÇ3!<ÍCZ(ç´¾êËAÿ¹ÈM<âIP®‘ŠäZô§­Í¼â^zóIÊmøõ…ô ğœ¾C¥-¢›K¹M|c½°b¼ã7‰¢Í%´2d¢³'MšTq\ììLu%$QÊå`ëcu¯ŸÃ¬å|(î¶á†9I1bØvÒ(ºX ‡L°_ÕÎÊ§Ó‚ƒ—äö‘¿~èñ„oõuÉÍag’°ÊoûèR×\Z—€’¡l°Z­+u¨£É×Ï˜¿ÇïZWM6¦«T±™¼rˆ”õ<.T_‘£×O­šÊÏ•‘µk|!"Ø¢}ÂE²á?™+vvtíW=ÄŸAÖÒ/rº™ëA]*³è}Tv¹¹e’iÛŸD‚0Hı
GgõLÍ¯ÚLFXõh†Õë(“*mz0@½Ò4År¶É™\œÙB½F—3Í¥çscœW6_I2`œàæˆPZñ££Œ8\Ó¿@¨NÓæ™ËÑ]FêiáÌ“&™®—®ÇiŞªLí‹Å ¾ÉlZ'jjhQ6e<‡wŸOOûë-½¦êŠXEŞìJƒ‰æÌ´œBì­æ~_ÒÄË‰|¨„š¬¸7}/#®ªƒ–î@üpñ¨i(©|ıMRˆ*)Û½’î‘4ï/"mãÈ—îãAWn1ÿ;Ã(j3~«ùÿºüoo´_ËÿÆûÃQ—ÿİEùíßŞ½8ûWÏÜÀ:?~ûQ}ßUÎ?µ|O@‘
ËzùÇ´ş=\îìĞ¯×§/NH€Õsgggo%¿zîì9şá°°/Á>‚ı#dü+>b`‡3°­ÓWšÌÓWˆôğ?›¹ø%L–´}á7}"ÊŸÀ¯[jŒ}Ë*¿UĞhûÖÃ_·N_õóŸ@¿d›}°E…[ie’©Ç	C¥ ¥® e© ¥õKÆ¢q”•U&%‰:ƒj¤^äÚìÌ–¥&d¢Èµ.*ËÒ§p¢7M2ôUéQ…L@Çô±G¢ÑZ–ãqL¬‡väƒ½€íİŠº;ß|7ş_Ğƒ{óÿÃÃqÿG‡ÿ¿ü/ŒØ¥Ï@×€?,Ÿeyÿ‘E+—Å±JÉ²Ø0LgëLªq¢ n 'LËôSæ‹Í”ŠŠÌyŒáwQ«çšP»¶…¨²Í
¡—’¬l°‘{Å>©æù8„˜k‰eÄÌç-#ÑyA6ÅøSëvÖÕ·ßÃúÇ{uüÿà Ãÿïÿ¯ú–¥g»Ö'ƒÒ–1,ë•u
ñÙM–™¢İÆ!s$ÙŞ0«¬ „Íd‰x|!BĞ“­kë€é4€İÔ»¬é>üéÎHç ÷ˆHJØp#Ç17ñ(”­@tZ`ÛM°ØÁ ŞåğN—ĞS'?…ÒnÏ®Åe7d£5`²zñZa­Ôâ¿@Kõ.Úv'ç8Åë8ıqÇ›Ğ›š%+áM™ê[Q6	±fP›z€®vàæñ³G­øÙ€Ø: YÇ¢ÍìÇ‡}k¢Ş#pœƒeãôÈØš	Ä6 ÔÂÓA\ºHo‚DëÚqãsİCæ& œdÂÕqÂtÍq†‚êìhugìæeæº?’ç®‹jºöO­Iªa©š&ª{Õš˜w¸·Ô¨®¾_}¯í˜Y³ÿ-ï%ÿÛ?Ü×ã¿½½ÿ»×ü/CØv—G›æ„Æ[ YX®…–dQ_,SÓÓ–˜OËİÜ(IÑy}¯ŠªævYÈVKøTPÖ%=Ú¦Ñ×”¶ús:CË|J‹¸Êù(ñ|an"÷ƒ< £4"ƒTa{St5¾¸Rçƒ€ûˆ«‚ºF­‰qN%]Ù(e?ŞÓ6!/QĞµ3—áTê‰÷yMÇ$ÕäËº6gÏ…n¦ôÕ=–ÆsŠ*÷0°áÓù«ó‰œ¢Ìú€9c!á«€€”[<pX§æùı–æ(ğ54Ö‚(åûŸ>|ÃV–‰õİ$nlÈØI–€ƒ–6ãÒTø¥"°º­­"¾Må6lcC›»ŠwaÉY<ŠDV9¨7H‰Uåc>½¡‡3‚ËùÅl[6}»åc¶á-7Z)ipM7dH»qAğR:ˆëA¦t:€^¤“¸"ˆ)œu–à‹¹œ¥OI8½Õ®4ØöÑkÅQĞ%Hƒ0	wèd[„°Š0”‹•÷Ãd•zğ¯”§|p…”"êW…rö•x¤Ò™=50×
ÏBJ,}>Ñ]]¶Pp:pš#i%[2«“¶³(î½piâã¾uüùäãÄÚXwºÿ‡÷vş7<ÖñßÑá^·ÿß-ş£mÛÒ0'“j.+qM|N¢t¦rz©v/õ¼5«èFEğ&pFÎÉû°hoFr•À)dÙ¨–Â©>èy‘)UÌZÎoÊH!»Eº£$™S•TºXÃ¿·1K.µû(¶j^^ËJ*Èquàkî\íæµÓî.Æÿáù_~º|oç£½ñÓîşÇ½ûıª¿•E¥n‰ß¶·á÷ìzõÂ½¡Ë‚G¿"˜¥—ñIñR¤Ş\º-B")œÃhâT†Ú‹ÔóV»Y€µpœ&ê.¡ï^.
fcº‡/è¡”šº×®Eğ‰éZ5¥JØì“BL,(I[‹0Úg1&Å‹˜óG0y¥1ªª‡ÀËüZ=m`åûiƒpAwê‰(»\ß$ˆ™ÇæD`¸Uß¤¾”wŞ/r’vTÓ-ø&cÈY¬³µ^W7ğ.ËÛëºˆ¶kí¦AfÚuîMn¾÷T¶–_J„íÜĞÔDq[±—ë=C•æ´ö‘¼—O«‰¬U«Õ²÷ás†’‹YoÈÒ©Åi«3efĞ/Ë÷NEêÆô>‹4™C=9§$o¿N“ãësÂ¾v,fmÕø5|rR–4ìÆı‰Ïç+êPÓÊ6à>a+†S³°µt&¢¤µƒ&=[õü?Póo]ß_ÁÛ¨Õ(tâÁ|%Wô¹ç¹Ôtoÿ¦·£µO#	°ÕcDƒ6®®¨Âs	©Ç.é^h#S1é°ÿšñ_±ïßWş?:¨ßÿ÷ºøïñÿÖW<%XVBûÅ®>ÉaÕ‚ıåÛ	Óæ3ã«%İw¹Š¬ş©w#uÉ¬É¶ño%Ì¯ŞŸÀÍƒWİ@ZÕ°æ¿ş‰ÏÁ€X†±”w»b®Çf/OÊñæ;9Åû=qõ¨£,µÜµ‹+ºUè|ó”’ßw£ñe•–n|Å ª¯ekCâoéÒ\WºÒ•®t¥+]éJWºÒ•®t¥+³òß9Ó; P  