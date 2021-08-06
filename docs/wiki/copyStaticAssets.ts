import * as shell from 'shelljs';

shell.cp('-R', 'src/public/scripts/lib', 'dist/scripts/js');
shell.cp('-R', 'src/public/assets/fonts', 'dist/assets/fonts');
shell.cp('-R', 'src/public/assets/images', 'dist/assets/images');
shell.cp('-R', 'src/public/assets/icons', 'dist/assets/icons');
