#!/bin/bash

# Usage : ./concat_sources.sh [répertoire_de_travail] [fichier_de_sortie] [motif1] [motif2] ...
# Par défaut : répertoire courant, output.txt, et aucun motif d'exclusion

ROOT_DIR="${1:-.}"
OUTPUT_FILE="${2:-output.txt}"
shift 2  # Décale les arguments pour ne garder que les motifs d'exclusion

EXCLUDE_PATTERNS=("$@")  # Tableau de motifs d'exclusion

# Nettoyage de l'ancien fichier de sortie
> "$OUTPUT_FILE"

# Recherche des fichiers .c, .h, .cpp, .hpp et .inl (triés pour consistance)
find "$ROOT_DIR" -type f \( -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp" -o -name "*.inl" \) | sort | while read -r FILE; do
    EXCLUDE_FILE=false

    # Vérifier si le fichier correspond à l'un des motifs d'exclusion
    for PATTERN in "${EXCLUDE_PATTERNS[@]}"; do
        if [[ -n "$PATTERN" && "$FILE" =~ $PATTERN ]]; then
            echo "Exclusion de : $FILE"
            EXCLUDE_FILE=true
            break
        fi
    done

    if $EXCLUDE_FILE; then
        continue
    fi

    REL_PATH="${FILE#$ROOT_DIR/}"  # Chemin relatif
    echo "\`\`\`" >> "$OUTPUT_FILE"
    echo "// @file $REL_PATH" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE"
    cat "$FILE" >> "$OUTPUT_FILE"
    echo -e "\n" >> "$OUTPUT_FILE"
    echo "\`\`\`" >> "$OUTPUT_FILE"
done

echo "Fichiers concaténés dans : $OUTPUT_FILE"
