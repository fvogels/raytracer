cat data/$1.ply | ruby convert-ply.rb | ruby transform.rb --scale Y --corner | ruby bbh.rb > $1.mesh
