"use strict";

// Include gulp.
const gulp         = require('gulp'),
      sass         = require('gulp-sass'),
      $            = require('gulp-load-plugins')(),
      autoprefixer = require('gulp-autoprefixer'),
      sourcemaps   = require('gulp-sourcemaps'),
      cssnano      = require('gulp-cssnano'),
      rename       = require("gulp-rename"),
      plumber      = require('gulp-plumber'),
      notify       = require('gulp-notify'),
      browserSync  = require("browser-sync").create(),
      del          = require('del');
let cleanCSS       = require('gulp-clean-css');

sass.compiler      = require('node-sass');

var paths = {
  style: {
    src: 'sass/**/*.scss',
    dest: './css'
  },
  img: {
    src: './img'
  },
  scripts: {
    src: 'src/scripts/**/*.js',
    dest: 'assets/scripts/'
  },
  browser: {
    proxy: 'http://localhost/agenda'
  },
  autoprefixer:{
    grid: true,
    browsers: [
      'last 5 versions',
      '> 1%',
      'Ie 9',
      'Ie 10',
      'Ie 11'
    ]
  }
};

/*
 * Funcion of compile sass
 */
function styles() {
  return gulp.src(paths.style.src)
  .pipe(plumber({
    errorHandler: function (error) {
      notify.onError({
        title:    'Gulp',
        subtitle: 'Failure!',
        message:  'Error: <%= error.message %>',
        sound:    'Beep'
      }) (error);
      this.emit('end');
    }
  }))
  .pipe($.sourcemaps.init())
  .pipe(sass.sync({ outputStyle : 'expanded' }).on('error', sass.logError))
  .pipe($.autoprefixer(paths.autoprefixer))
  .pipe(cleanCSS())
  .pipe(rename({suffix: '.min'}))
  .pipe($.sourcemaps.write('./maps'))
  .pipe(gulp.dest(paths.style.dest))
  .pipe(browserSync.stream());
}

/*
 * CSS minifi
 */
function css_minify(done) {
  return gulp.src('./css/agenda.css')
		// .pipe(cssnano())
		.pipe(cleanCSS())
		.pipe(rename({suffix: '.min'}))
    .pipe(gulp.dest(paths.style.dest))
    // .pipe(browserSync.stream());
}

/*
 * Clear .mapa
 */
function clean() {
  return del(["./css/maps"]);
}

/*
 * Clear browser-sync
 */
function reload() {
  browserSync.reload();

}

function browserSyn(done) {
  browserSync.init({
    proxy: paths.browser.proxy,
    port: 3000
  });
  done();
}

/*
 * Funtion Watch
 */
function watchFiles() {
  gulp.watch(paths.style.src, styles, reload);
  // gulp.watch(paths.style.src, gulp.series(css_minify));
}

/*
 * Specify if tasks run in series or parallel using `gulp.series` and `gulp.parallel`
 */
const build = gulp.series(clean, gulp.parallel(styles));
const watch = gulp.series(styles, gulp.parallel(watchFiles,browserSyn));

/*
 * You can use CommonJS `exports` module notation to declare tasks
 */
exports.styles = styles;
exports.clean = clean;
exports.css_minify = css_minify;
exports.build = build;
exports.watch = watch;

/*
 * Define default task that can be called by just running `gulp` from cli
 */
exports.default = build;




