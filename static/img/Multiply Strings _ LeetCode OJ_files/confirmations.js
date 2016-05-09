/**
 * Created by Daniel on 26/03/2016.
 */
var confirmations = {
  confirm_see_solution: function (e, url, is_ac) {
    e.preventDefault();
    if (!is_ac) {
      swal({
        title: "Are you sure?",
        text: "You have not solved this problem yet. Are you sure you want to view the solution?",
        type: "info",
        showCancelButton: true,
        confirmButtonText: "Yes, see the solution!",
        closeOnConfirm: false
      }, function () {
        window.location.href = url;
      });
    }
    else {
      window.location.href = url;
    }
  },

  requestSolution: function (e, requested, request_url) {
    e.preventDefault();
    swal({
      title: "Request Editorial Solution?",
      text: "The solution is not available yet. Would you like to submit a request for this solution?",
      type: "info",
      showCancelButton: true,
      showLoaderOnConfirm: !requested,
      confirmButtonText: "Yes, request!",
      closeOnConfirm: false
    }, function (isConfirm) {
      if (isConfirm) {
        if(requested) {
          swal("Already Requested", "You have already requested for this question's solution before.");
        }
        else {
          $.ajax({
            type: "GET",
            url: request_url,
            success: function(data) {
              swal("Requested!",
                "Your request for editorial solution has been received",
                "success");
            },
            error: function(data) {
              swal("Already Requested", "You have already requested for this question's solution before.");
            }
          });
        }
      }
    });
  }
};
