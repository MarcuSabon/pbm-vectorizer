start=$(date +%s.%N)
./test_bezier3 "dossier_pbm/zebre_dur.pbm" "dossier_eps/zebre_dur.eps" "$d"
end=$(date +%s.%N)
duration=$(echo "$end - $start" | bc)
echo "⏱️ Temps d'exécution : ${duration}s"
