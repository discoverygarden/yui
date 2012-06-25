<?php

/**
 * @file
 *
 * A collection of helper/utility functions for this module.
 */

/**
 * Returns the path to the YUI library.
 *
 * @return string
 *  The path to the YUI library if found, FALSE otherwise.
 */
function yui_get_path() {
  static $path;
  if (isset($path)) {
    return $path;
  }
  $path = FALSE;
  if (function_exists('libraries_get_path')) { // Libraries API integration.
    $path = libraries_get_path('yui');
    if ($path !== FALSE && !file_exists($path)) {  // Libraries API 1.x returns a default path; 2.x returns FALSE.
      $path = FALSE;
    }
  }
  // Manually check sites/all/libraries in case Libraries API is not available.
  elseif (file_exists('./sites/all/libraries/yui')) {
    $path = 'sites/all/libraries/yui';
  }
  return $path;
}

/**
 * Gets the installed version of YUI
 *
 * @return string
 *  The currently installed version, if found FALSE otherwise.
 */
function yui_get_version() {
  static $version;
  if(isset($version)) {
    return $version;
  }
  $version = FALSE;
  $filename = yui_get_path() . 'build/yui/yui.js';
  if(file_exists($filename)) {
    $text = file_get_contents($filename);
    $matches = array();
    preg_match('/VERSION[ ]*\=[ ]*\'(.*)\'/', $text, $matches);
    if(isset($matches[1])) { // The first sub expression.
      $version = $matches[1];
    }
  }
  return $version;
}