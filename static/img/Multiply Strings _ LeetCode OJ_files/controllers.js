'use strict';

/* Controllers */

angular.module('questionList', [])
  .controller('questionListCtrl', ['$scope', '$http', function ($scope, $http) {
    $http.get(
      '/app/problemset/data.json'
    ).success(function(data) {
      $scope.problems = data;
    });

    $scope.orderProp = 'title';

  }]);

angular.module('app')
  .controller('questionDetailCtrl', ['$scope', '$http', '$timeout', function($scope, $http, $timeout) {
    var vm = this;
    vm.init = function(question_id, is_favor, url_favor) {
      vm.question_id = question_id;
      vm.is_favor = is_favor;
      vm.url_favor = url_favor;
      vm.is_alert = false;
      decide_popover(vm.is_favor);
    };

    var decide_popover = function(is_favor) {
      if (is_favor) {
        vm.popover = "delete from favorite";
      } else {
        vm.popover = "save to favorite";
      }
    };

    vm.favor = function() {
      var method = '';
      if (vm.is_favor) {
        method = 'delete';
      } else {
        method = 'post'
      }
      $http({
        method: method,
        url: vm.url_favor,
        data: {
          qid: vm.question_id
        }
      }).success(function(data) {
        vm.is_favor = data.is_favor;
        decide_popover(vm.is_favor);
      }).error(function(data, status) {
        if (status == '404') {
          vm.is_alert = true;
          $timeout(function() {
            vm.is_alert = false;
          }, 2000);
        }
      })
    }
  }]);
