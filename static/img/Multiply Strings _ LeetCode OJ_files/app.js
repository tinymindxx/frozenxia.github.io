(function() {
  'use strict';

  angular.module('app', [
    'ngAnimate',

    'filters',

    'aceEditor',
    'aceEditorDirectives',
    'submissionPoller'
  ])
  .constant('rootDir', '/static/angular/'
  )
  .config(['$interpolateProvider', function($interpolateProvider) {
    $interpolateProvider.startSymbol('{[{');
    $interpolateProvider.endSymbol('}]}');
  }])
  .config(function($httpProvider) {
    $httpProvider.defaults.headers.common['X-Requested-With'] = 'XMLHttpRequest';
    $httpProvider.defaults.headers.delete = {'Content-Type': 'application/json'};
    $httpProvider.defaults.xsrfCookieName = 'csrftoken';
    $httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
  });
})();
